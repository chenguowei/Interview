//
// Created by 陈国威 on 2018/4/15.
//
/**
 * 添加一个定时器的时间复杂度是 O(1),删除一个定时器的时间复杂度也是O(1)
 * 执行一个定时器的时间复杂度是O(N)
 *
 * */


#include <time.h>
#include <netinet/in.h>
#include <stdio.h>


#define BUFFER_SIZE 64

class tw_timer;

/* 解绑 socket和定时器 */
struct client_data
{
  sockaddr_in	address;
  int sockfd;
  char buf[BUFFER_SIZE];
  tw_timer* timer;
};

/* 定时器类 */
class tw_timer
{
 public:
  tw_timer(int rot, int ts)
	  : next(NULL),
		prev(NULL),
		rotation(rot),
		time_slot(ts)
  {

  }

 public:
  int 	rotation;	// 记录定时器在时间轮转多少圈后生效
  int	time_slot;	// 记录定时器属于时间轮上的哪个曹
  void (*cb_func) (client_data *);	// 定时器的回调函数
  client_data*	user_data;		// 客户数据
  tw_timer*	next;	// 指向下一个定时器
  tw_timer*	prev;	// 指向前一个定时器
};


class time_wheel
{
 public:
  time_wheel() : cur_slot(0)
  {
	for (int i = 0; i < N; ++i)
	  {
		slots[i] = NULL;	/* 初始化每个槽的头结点*/
	  }
  }

  ~time_wheel ()
  {
	/* 遍历每个槽，并销毁其中的定时器 */
	for (int i = 0; i < N; ++i)
	  {
		tw_timer* tmp = slots[i];
		while (tmp)
		  {
			slots[i] = tmp->next;
			delete tmp;
			tmp = slots[i];
		  }
	  }
  }


  /* 根据定时值 timeout 创建一个定时器，并把它插入合适的槽 */
  tw_timer* add_timer(int timeout)
  {
	if (timeout < 0)
	  {
		return NULL;
	  }

	int ticks = 0;
	/* 下面根据待插入定时器的超时值计算它将在时间轮转动 多少个滴答后被触发，并将
	 * 该滴答数存储于变量 ticks中，如果待插入定时器的超时值小于时间轮的槽间隔SI,
	 * 则将 ticks 折上为1，否则将将 ticks 向下折合为 timeout/SI
	 * */

	if (timeout < SI)
	  {
		ticks = 1;
	  }
	else
	  {
		ticks = timeout / SI;

	  }
	/* 计算待插入的定时器在时间轮转动多少圈后被触发 */
	int rotation = ticks / N;
	/* 计算待插入的定时器应该插入哪个槽中 */
	int ts = (cur_slot + (ticks % N)) %N;
	/* 创建新的定时器，它在时间轮转动 rotation圈之后被触发，且处在第 ts 个槽中 */
	tw_timer* timer = new tw_timer(rotation, ts);

	/* 如果第ts 个槽中尚无任何定时器，则把新建的定时器插入其中
	 * 并将该定时器设为槽的头结点
	 * */
	if (!slots[ts])
	  {
		printf ("add timer, rotation is %d, ts is %d, cur_slot is %d\n",
			rotation, ts, cur_slot);
		slots[ts] = timer;
	  }
	else
	  {
		timer->next = slots[ts];
		slots[ts]->prev = timer;
		slots[ts] = timer;
	  }

	return timer;
  }

  /* 删除目标定时器 timer, 并返回下一个定时器 */
  tw_timer* del_timer(tw_timer* timer)
  {
	if (!timer)
	  {
		return NULL;
	  }

	int ts = timer->time_slot;
	tw_timer* tmp;
	/* slots[ts] 是目标定时器所在槽的头结点，则重置该槽的头结点*/
	if (timer == slots[ts])
	  {
		slots[ts] = slots[ts]->next;
		if (slots[ts])
		  {
			slots[ts]->prev = NULL;
		  }
	  }
	else
	  { //因为该函数只给 tick()调用，已经找到timer的具体的位置了
		timer->prev->next = timer->next;
		if (timer->next)
		  {
			timer->next->prev = timer->prev;
		  }
	  }
	tmp = timer->next;
	delete timer;
	return tmp;
  }


  /* SI 时间到后，调用该函数，时间轮向前滚动一个槽的间隔*/
  void tick()
  {
	tw_timer* tmp = slots[cur_slot];	// 取得时间轮上当前槽的头结点
	printf ("current slot is %d\n", cur_slot);
	while (tmp)
	  {
		printf ("tick the timer once\n");
		//如果要想设置该定时器再次启动，则再次插入到时间轮中

		/* 如果定时器的 rotation 值大于0，则它在这一轮不触发 */
		if (tmp->rotation >  0)
		  {
			tmp->rotation--;
			tmp = tmp->next;
		  }

		/* 否则，说明定时器已经到期，于是执行定时任务，然后删除定时器 */
		else
		  {
			tmp->cb_func(tmp->user_data);
			/* 如果要设置循环定时器（每经过多少 s 执行的定时器），则
			 * 则删除定时器后，将它再次插入到时间轮中
			 * */
			tmp = del_timer (tmp);
		  }
	  }

	cur_slot = ++cur_slot % N;	// 更新下一个时间轮的当前槽，以放应时间轮的转动
  }

 private:
  /* 时间轮上的槽的数目 */
  static const int N = 60;
  /* 每1 s 时间转动一次， 即槽间隔为 1 s */
  static const int SI = 1;
  /* 时间轮的槽， 其中每个元素指向一个定时器链表，链表无序 */
  tw_timer*	slots[N];
  int cur_slot;		/* 时间轮的当前槽 */
};