//
// Created by 陈国威 on 2018/3/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int key_t;
typedef int data_t;

typedef enum color_t
{
  RED = 0;
  BLACK =1;
} color_t;


typedef struct rb_node_t
{
  struct rb_node_t*	parent;
  struct rb_node_t*	left;
  struct rb_node_t*	right;
  key_t key;
  data_t data;
  color_t color;
} rb_node_t;

/* forward declaration */
rb_node_t*	rb_insert(key_t key, data_t data, rb_node_t* root);
rb_node_t*	rb_search(key_t key, rb_node_t* root);
rb_node_t*	rb_erase(key_t key, rb_node_t* root);
static rb_node_t* rb_insert_rebalance(rb_node_t *node, rb_node_t *root);
static rb_node_t* rb_erase_rebalance(rb_node_t *node, rb_node_t *parent, rb_node_t *root);

    static rb_node_t* rb_new_node(key_t key, data_t data)
{
  rb_node_t* node = (rb_node_t*) malloc (sizeof (rb_node_t));

  if (!node)
    {
      printf ("malloc error\n");
      exit (-1);
    }

  node->key = key;
  node->data = data;

  return node;
}

/*-----------------------------------------------------------
|   node           right
|   / \    ==>     / \
|   a  right     node  y    左旋转
|       / \       / \
|       b  y     a   b
 -----------------------------------------------------------*/

static rb_node_t* rb_rotate_left(rb_node_t* node, rb_node_t* root)
{
  rb_node_t* right = node->right;     //指定指针指向 right<--node->right

  if ( (node->right = right->left))
    {
      right->left->parent = node;
    }
  right->left = node;     //node 成为right 的左孩子

  if ( (right->parent = node->parent))  //node有根结点
    {
      if (node == node->parent->right)  //node是右结点
        {
          node->parent->right = right;
        }
      else
        {
          node->parent->left = right;
        }
    }
  else  //root 为空
    {
      root = right;
    }

  node->parent = right;   //right成为node的父母

  return root;

}

/*-----------------------------------------------------------
|       node           left
|       / \            / \
|    left  y   ==>    a   node  右旋转
|   / \                    / \
|  a   b                  b   y
-----------------------------------------------------------*/
static rb_node_t* rb_rotate_right(rb_node_t* node, rb_node_t* root)
{
  rb_node_t*  left = node->left;

  if ( (node->left = left->right))    //使 node 的左结点成为 left的右结点
    {
      left->right->parent = node;
    }
  left->right = node;

  if ( (left->parent = node->parent))
    {
      if (node == node->parent->right)
        {
          node->parent->right = left;
        }
      else
        {
          node->parent->left = left;
        }
    }
  else
    {
      root = left;
    }

  node->parent = left;

  return root;
}

// 红黑树查找结点
// rb_search_auxiliary: 查找
// rb_node_t* rb_search: 返回找到的结点
static rb_node_t* rb_search_auxiliary(key_t key, rb_node_t* root, rb_node_t** save)
{
  rb_node_t* node = root, *parent = NULL;
  int ret;

  while (node)
    {
      parent = node;
      ret = node->key - key;
      if (ret > 0)  //key 比结点小
        {
          node = node->left;
        }
      else if (ret < 0) // key 比结点大
        {
          node = node->right;
        }
      else
        {
          return node;
        }
    }

  if (save)
    {
      *save = parent;
    }

  return NULL;
}


// 返回上述 rb_search_auxiliary 查找结果
rb_node_t* rb_search(key_t key, rb_node_t* root)
{
  return rb_search_auxiliary (key, root, NULL);
}


/*-----------------------------------------------
|
| 红黑数的插入结点
|
|------------------------------------------------*/

rb_node_t* rb_insert(key_t key, data_t data, rb_node_t* root)
{
  rb_node_t* parent = NULL, *node;

  parent = NULL;
  if ( (node = rb_search_auxiliary (key, root, &parent)) ) //调用rb_search_auxiliary找到插入结点的地方
    { // 在红黑树中已经有了该结点
      return root;
    }

  node = rb_new_node (key, data); //分配结点
  node->parent = parent;
  node->left = node->right = NULL;
  node->color = RED;

  if (parent) //红黑树不为空
    {
      if (parent->key > key)
        {
          parent->left = node;
        }
      else
        {
          parent->right = node;
        }
    }
  else
    {
      root = node;
    }

  return rb_insert_rebalance (node, root);  //插入结点后，调用rb_insert_rebalance 修复红黑树
}

//五、红黑树的3种插入情况
//接下来，咱们重点分析针对红黑树插入的3种情况，而进行的修复工作。
//--------------------------------------------------------------
//红黑树修复插入的3种情况

//插入情况1：z的叔叔y是红色的。
//插入情况2：z的叔叔y是黑色的，且z是右孩子
//插入情况3：z的叔叔y是黑色的，且z是左孩子
//为了在下面的注释中表示方便，也为了让下述代码与我的倆篇文章相对应，
//用z表示当前结点，p[z]表示父母、p[p[z]]表示祖父、y表示叔叔。
//--------------------------------------------------------------
static rb_node_t* rb_insert_rebalance(rb_node_t* node, rb_node_t* root)
{
  rb_node_t* parent, *gparent, *uncle, *tmp;  //父母p[z], 祖父p[p[z]], 叔叔y, 临时结点*tmp

  while ( (parent = node->parent) && parent->color == RED)
    {
      // parent 为 node 的父母，且当父母的颜色为红时
      gparent = parent->parent;   //gparent 为祖父

      if (parent == gparent->left)  // 当祖父的左孩子即为父母时
        {
          uncle = gparent->right;   //定义叔叔的概念，叔叔y就是父母的孩子

          if (uncle && uncle->color == RED) // 情况1： z的叔叔y 时红色
            {
              uncle->color = BLACK;   // 将叔叔结点y着为黑色
              parent->color = BLACK;  // z 的父母p[z] 也着为黑色。解决z, p[z] 都是红色的问题
              gparent->color = RED;
              node = gparent;     //将祖父当做新增结点z， 指针z上移两层，且着为红色
            }
          else                              // 情况2：z的叔叔y是黑色 （包括叔叔为空结点，因为空结点也是黑色）
            {
              if (parent->right == node)    //且 z为右孩子
                {
                  root = rb_rotate_left (parent, root);
                  tmp = parent;
                  parent = node;
                  node = parent;  // parent 与node 互换角色
                }

                                            // 情况3：z的叔叔y是黑色，此时z 成为了左结点
                                                    //注意，1：情况3 是由上述情况2变化而来的
                                                    //.....2: z的叔叔总是黑色的，否则就是情况1 了
              parent->color = BLACK;    // z的父母p[z]着为黑色
              gparent->color = RED;     // 原祖父结点着为红色
              root = rb_rotate_right (gparent, root);
            }
       }

      else
        {
          uncle = gparent->left;    // 祖父的左孩子作为叔叔结点。 原理跟上面一样
          if (uncle && uncle->color == RED)   // 情况1：z 的叔叔y是红色
            {
              uncle->color = BLACK;
              parent->color = BLACK;
              gparent->color = RED;
              node = gparent;     // 同上
            }
          else                                // 情况2：z 的叔叔y是黑色
            {
              if (parent->left == node)   // 且z为左孩子
                {
                  root = rb_rotate_right (parent, root);  // 以结点parent, root 右旋
                  tmp = parent;
                  parent = node;
                  node = parent;  // parent 与node 互换角色
                }

              // 经过情况2的变化，成为了情况3
              parent->color = BLACK;
              gparent->color = RED;
              root = rb_rotate_left (gparent, root);  // 以结点gparent 和 root 左旋

            }
        }
    }

  root->color = BLACK;  //根结点，不论怎样，都得置为黑色
  return root;
}

//---------------------------------------------------
//
//  红黑树的删除
//
//---------------------------------------------------
static rb_node_t* rb_erase(key_t key, rb_node_t* root)
{
  rb_node_t *child, *parent, *old, *left, *node;
  color_t color;

  child = NULL;

  if ( !(node = rb_search_auxiliary (key, root, NULL))) //调用rb_search_auxiliary查找要删除的结点
    {
      printf ("key %d is not exist\n", key);
      return root;
    }

  old = node;

  if (node->left && node->right)  // 要删除的结点的左右结点都存在
    {
	  node = node->right;
      while ( (left = node->left) != NULL)
        node = left;      // 寻找后继结点 （就是删除结点的右子树中最小的结点）

      child = node->right;
      parent = node->parent;
      color = node->color;

      if (child)  // 如果右子树中最小的结点有右结点
        {
          child->parent = parent;
        }

      if (parent)
        {
          if (parent->left == node) // 如果右边最小结点 位于左结点
            {
              parent->left = node;
            }
          else
            {
              parent->right = node;
            }
        }
      else
        {
          root = child;
        }

      if (node->parent == old)
        {
          parent = node;
        }

      node->parent = old->parent;
      node->color = old->color;
      node->left = old->left;
      node->right = old->right;

      if (old->parent)
        {
          if (old->parent->left == old)
            {
              old->parent->left = node;
            }
          else
            {
              old->parent->right = node;
            }
        }
      else
        {
          root = node;
        }

      old->left->parent = node;
      if (old->right)
        {
          old->right->parent = node;
        }
    }
  else
    {
      if (!node->left)  // 如果删除结点没有左结点
        {
          child = node->right;
        }
      else if (!node->right)  // 如果删除结点没有右结点
        {
          child = node->left;
        }

      parent = node->parent;
      color = node->color;

      if (child)  // 修改child 的指针
        {
          child->parent = parent;
        }
      if (parent)
        {
          if (parent->left == node)
            {
              parent->left = child;
            }
          else
            {
              parent->right = child;
            }
        }
      else
        {
          root = child;
        }
    }

  free (old);
  if (color == BLACK)
    {
      root = rb_erase_rebalance(child, parent, root); // 调用rb_erase_rebalance 来恢复红黑树性质
    }

  return root;
}


//七、红黑树的4种删除情况
// 情况1：x的兄弟w是红色的。

// 情况2：x的兄弟w是黑色的，且w的俩个孩子都是黑色的。

// 情况3：x的兄弟w是黑色的，w的左孩子是红色，w的右孩子是黑色。

// 情况4：x的兄弟w是黑色的，且w的右孩子时红色的。
//----------------------------------------------------------------
//红黑树修复删除的4种情况
//为了表示下述注释的方便，也为了让下述代码与我的倆篇文章相对应，
//x表示要删除的结点，*other、w表示兄弟结点，
//----------------------------------------------------------------

static rb_node_t* rb_erase_rebalance(rb_node_t *node, rb_node_t *parent, rb_node_t *root)
{
  rb_node_t   *other, *o_left, *o_right;  // x的兄弟*other, 兄弟左孩子*o_left, 兄弟右孩子*o_right

  while ( (!node || node->color == BLACK) && node != root)
    {
      if (parent->left == node)   // 结点为左结点
        {
          other = parent->right;
          if (other->color == RED)  //情况1：x的兄弟w是红色
            {
              other->color = BLACK;
              parent->color = RED;  // 上两行，改变颜色，w->黑，p[x]->红
              root = rb_rotate_left (parent, root);
              other = parent->right;  // x 的新兄弟new w 是旋转之前w的某个孩子
            }

          if ( (!other->left || other->left->color == BLACK) &&
               (!other->right || other->right->color == BLACK))
            // 情况2：x的兄弟w是黑色，且w的两个孩子也是黑色
            {
              //  由于w和w的两个孩子都是黑色的，则在 x 和 w 上得去掉一个黑色
              other->color = RED;   // 于是，兄弟w变为红色
              node = parent;        // p[x] 为新结点x
              parent = node->parent;  // x<-p[x]
            }
          else
            {   // 情况3：x的兄弟w是黑色，且w的左孩子是红色，右孩子是黑色
                if (!other->right || other->right->color == BLACK)
                  {
                    if ( (o_left = other->left))  // w和其左孩子left[w], 颜色互换
                      {
                        o_left->color = BLACK;
                      }
                    other->color = RED;   // w由黑->红
                    root = rb_rotate_right (other, root); //再对w 进行右旋，从而红黑性质恢复
                    other = parent->right;    // 变化后的，父节点的右孩子，作为新的兄弟结点

                  }

              // 情况4：x的兄弟w是黑色
              other->color = parent->color;   // 把兄弟节点染成当前节点父节点的颜色
              parent->color = BLACK;          // 把当前节点父节点染成黑色
              if (other->parent)  // 且w的右孩子是红
                {
                  other->right->color = BLACK;  // 兄弟节点w右孩子染成黑色
                }
              root = rb_rotate_left (parent, root); // 并再做一次左旋转
              node = root;  // 并把 x置为根
              break;
            }
        }

        // 下述情况与上述情况，原理一致。
      else
        {

        }
    }
}