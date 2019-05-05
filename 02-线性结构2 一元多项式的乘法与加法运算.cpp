#include <iostream>
#define NOISE 0
class polnode {//每个点都有系数指数,和指向下一个点的指针
	public:
		int coe , exp ;
		polnode * next ;
		polnode() {
			coe=0;
			exp=0;
			polnode * next=0;
			if (next!=0)std::cout<<"polnode(): (next!=0)\n";

		}
		polnode(int c,int e) {//默认的话指针就是0，指数系数 都为0
			coe=c;
			exp=e;
			polnode * next=0;
			if (next!=0)std::cout<<"polnode(int c,int e): (next!=0)\n";
		}
};
class pollist {//送每一个多项式链表一个头尾指针
	private:
		polnode *head ,*tail;
		void selfadd(pollist & t1);
		void tailin(int c,int e);
		void deletepollist();
	public:
		pollist() {//每个新创建的pollist头尾指针都有同个零系数和零指数
			head=tail=new polnode(0,0);
		}
		void input();
		void output();
		void mul(pollist & L1,pollist & L2);
		void add(pollist & L1,pollist & L2);
};
void pollist::tailin(int c,int e) {

	polnode *temp= new polnode(c,e);//这个地方明明构造函数把next为零，却返回到这里的时候总是next不为零，拷贝函数不拷贝指针吗？
	if (NOISE)	if (temp->next!=0)	std::cout<<"tailin: new temp->next!=0\n";
	tail->next=temp;// 连上尾巴
	tail=temp;//现在是新的尾巴了
	if (NOISE)	if (tail->next!=0)	std::cout<<"tailin: new tail->next!=0\n";
	if(tail->next!=0)	tail->next=0;
	if (NOISE) {
		std::cout<<"tailin: "<<tail->coe<<" "<<tail->exp<<" have been attached to the tail!\n";
		if (tail->next==0)	std::cout<<"tailin: tail->next==0\n";
	}
}
void pollist::input() {
	if (NOISE)
		std::cout<<"input: num ";
	int num=0;
	std::cin>>num;
	if (NOISE)
		std::cout<<"input: num "<<num<<std::endl;

	int coe1,exp1;
	for(int i=0; i<num; i++) {
		if (NOISE)
			std::cout<<"input: coe&exp ";
		std::cin>>coe1>>exp1;
		if (NOISE)
			std::cout<<"input: coe "<<coe1 << " exp "<<exp1<<std::endl;
		if (NOISE)
			std::cout<<"input: into tailin---";
		tailin(coe1, exp1);
	}
}
void pollist::output() {
	int flag=1;//如果该函数结束1仍然不变,意味着一次if(tmp->coe)也没有进入，这个多项式里面每个项系数都是0
//	if (NOISE)	std::cout<<"\noutput:最开始的flag "<<flag<<std::endl;
	for (polnode* tmp = head->next; tmp != 0; tmp = tmp->next) {//跳过开头的空遍历每个点
		if(tmp->coe) { //不会输出系数为零的项
			if (flag!=1)
				std::cout<< " " <<tmp->coe << " "<<tmp->exp;
			if (flag==1) {
				std::cout << tmp->coe << " "<<tmp->exp;//输出第一系数非零项
				++flag; //flag从1变成了2， flag除了鉴别是不是全0项，还有鉴别出是否第一系数非零项的作用
//				if (NOISE)	std::cout<<"\noutput:第一系数非零项的++flag;  flag "<<flag<<std::endl;
			}
		}
	}
	if(flag==1) {
		std::cout<<"0 0";//这个多项式里面每个项系数都是0
//		if (NOISE)	std::cout<<"flag "<<flag<<std::endl;
	}
	if (NOISE)	std::cout<<"output: end "<<std::endl;
}
void pollist::add(pollist & L1,pollist & L2) {
	polnode *p1=L1.head->next;	//第一项我设了零所以直接跳过去
	polnode *p2=L2.head->next;
	while(p1 !=0 && p2 !=0) {
		if(p1->exp==p2->exp)     {

			if (NOISE)
				std::cout<<"add: into tailin---";
			tailin((p1->coe)+(p2->coe),p1->exp);
			p1 = p1 ->next;
			p2 = p2 ->next;
		} else if(p1->exp>p2->exp) {

			if (NOISE)
				std::cout<<"add: into tailin---";
			tailin((p1->coe),p1->exp);
			p1 = p1 ->next;
		} else {

			if (NOISE)
				std::cout<<"add: into tailin---";
			tailin((p2->coe),p2->exp);
			p2 = p2 ->next;
		}
	}
	if(p1 !=0) {

		if (NOISE)
			std::cout<<"add: into tailin---";
		tailin((p1->coe),p1->exp);
		p1 = p1 ->next;
	}
	if(p2 !=0) {

		if (NOISE)
			std::cout<<"add: into tailin---";
		tailin((p2->coe),p2->exp);
		p2 = p2 ->next;
	}
}
void pollist::mul(pollist & L1,pollist & L2) {
	polnode *p1=L1.head->next;//第一项我设了零所以直接跳过去,外循环已初始化
	pollist t1;
	while(p1 !=0  ) {//外多项式遍历完全之时方可跳出
		if (NOISE)
			std::cout<<"mul: 已进入外循环while(p1 !=0  )之中 "<<std::endl;
		if (NOISE)
			std::cout<<"mul: 此时外循环 "<<p1->coe<<" "<<p1->exp<<std::endl;
		polnode *p2=L2.head->next;//第一项我设了零所以直接跳过去,每轮外循环都会经历内循环初始化
		if (NOISE)
			std::cout<<"mul: 外循环马上进入内循环,把p2指针指向头项了 "<<std::endl;
		while(p2 !=0) { //	内多项式遍历完全之时方可跳出
			if (NOISE)
				std::cout<<"mul: 已进入内循环while(p2 !=0  )之中 "<<std::endl;
			if (NOISE)
				std::cout<<"mul: 此时内循环 "<<p2->coe<<" "<<p2->exp<<std::endl;
			int c =p1->coe * p2->coe ;// 内外系数相乘
			int e =p1->exp + p2->exp ;// 内外指数相加
			if (p1==L1.head->next) {
				tailin(c,e);//如果这是首次外循环，直接填充召唤这个method的多项式pm。
				if (NOISE)
					std::cout<<"mul:首次外循环，此时内循环变成了： "<<tail->coe<<" "<<tail->exp<<std::endl;
			} else {
				t1.tailin(c,e);//否则，填充t1，等一会内循环结束在本轮外循环结束之前加到pm身上
				if (NOISE)
					std::cout<<"mul:非首次外循环，该外循环，此时内循环t1现在变成了，待加： "
					         <<t1.tail->coe<<" "<<t1.tail->exp<<std::endl;
			}
			p2 = p2 ->next;
			if (NOISE)
				if(p2!=0 )
					std::cout<<"mul: 进入下一轮内循环  while(p2 !=0  )之中 "<<std::endl;
			if (NOISE)
				if(p2==0 )
					std::cout<<"mul: 内循环 完成~ "<<std::endl;
		}
		if (p1!=L1.head->next) {
			if (NOISE)
				std::cout<<"mul:非首次外循环，进入了外循环自加环节： "<<std::endl;
			selfadd(t1);
			if (NOISE)
				std::cout<<"mul: into selfadd(t1) "<<std::endl;
			t1.deletepollist();
			if (NOISE)
				std::cout<<"mul: into deletepollist "<<std::endl;
		}
		p1 = p1 ->next;
		if (NOISE) {
			if(p1!=0 )
				std::cout<<"mul: 将进入下一轮外循环了，请坐稳 "<<std::endl;
			else if(p1==0 )
				std::cout<<"mul: 外循环 完成~ "<<std::endl;
		}
	}
}
//解释 mul：两个多项式相乘，第一项我设了零所以直接跳过去，总体算法就是第一多项式每一项和第二多项式整体相乘
//（内循环干的事情）得到的所有多项式加到召唤这个method的多项式自身身上就是结果（外循环干的事情）。
//这函数有内外嵌套循环，首次外循环，直接填充召唤这个method的多项式。
//以后每次外循环开始一轮都可以得到一个刚自我清理好的新鲜多项式，过了内循环，被填充好了
//于是外循环接近尾声的时候，就会加到自身上
//并且清理了这个的多项式，下一轮外循环再填充它。
void pollist::selfadd(pollist & t1) { //自身多项式的话某项上的指数通常会比新造的那个对应位置项的指数要大
	polnode *p1=head->next;
	polnode *p2=t1.head->next;//第一项我设了零所以直接跳过去
	if (NOISE)
		std::cout<<"selfadd： 起初，p1指向： "<<p1->coe<<" "<<p1->exp<<std::endl;
	if (NOISE)
		std::cout<<"selfadd： 起初，p2指向： "<<p2->coe<<" "<<p2->exp<<std::endl;
	while(p2!=0 ) { //目标是把新鲜多项式项全整到自身多项式上去
		if (p1 !=tail) {
			if((p1->exp > p2->exp)&&(p1->next->exp < p2->exp)) {
				//自身de前一个项的指数比新鲜多项式的指数要大而后一个小
				if (NOISE)
					std::cout<<"selfadd： 前大后小之中 "<<std::endl;
				polnode* temp=new polnode(p2->coe,p2->exp);//创建新的项，插入
				temp->next=p1->next;//由后往前，重新整各自的next的现在指向
				p1->next=temp;//是因为是单向链表next指向后面那一个节点，所以由前往后还得保存后一个的地址

				p1=p1->next;//新塞入的项，它的指数是原来新鲜多项式最大的，所以今后由它开始塞咯
				if (NOISE)
					if(p1!=0 )
						std::cout<<"selfadd： 塞入该项后，新的p1指向： "<<p1->coe<<" "<<p1->exp<<std::endl;
				p2 = p2 ->next;
				if (NOISE)
					if(p2!=0 )
						std::cout<<"selfadd： 塞入该项后，新的p2指向： "<<p2->coe<<" "<<p2->exp<<std::endl;
			}

			else if((p1->exp > p2->exp)&&(p1->next->exp == p2->exp)) { //前一个自身项的指数比新鲜多项式的指数要大而后一个等于
				if (NOISE)
					std::cout<<"selfadd： 前大后等之中 "<<std::endl;
				p1=p1->next;//自身多项式指针就得指到那个指数相同的项咯
				p1->coe += p2->coe ;//不用造了，直接系数加一下就可以了
				if (NOISE)
					if(p1!=0 )
						std::cout<<"selfadd： 新的p1指向： "<<p1->coe<<" "<<p1->exp<<std::endl;
				p2 = p2 ->next;
				if (NOISE)
					if(p1!=0 )
						if(p2!=0 )std::cout<<"selfadd： 新的p2指向： "<<p2->coe<<" "<<p2->exp<<std::endl;
			}// 新塞入的项就可以不用在新鲜多项式里了再考虑，指针后移动！

			else if((p1->exp > p2->exp)&&(p1->next->exp > p2->exp)) { //前一个自身项的指数比新鲜多项式的指数要大而后一个也大
				p1=p1->next;//自身多项式指针就得往后挪动，下一个循环我们看看符合哪种情况呢？
				if (NOISE)
					std::cout<<"selfadd： 前大后大之中 "<<std::endl;
				if (NOISE)
					if(p1!=0 )
						std::cout<<"selfadd： 新的p1指向： "<<p1->coe<<" "<<p1->exp<<std::endl;
				if (NOISE)
					if(p1!=0 )
						std::cout<<"selfadd： p2指向不变啊~： "<<p2->coe<<" "<<p2->exp<<std::endl;
			}
			if (p1 ==tail)
				if (NOISE)
					std::cout<<"selfadd： p1指向了最后一个数！ "<<std::endl;
		}

		if(p1==tail&&p2!=0 ) { //结果自身多项式全扫完了新鲜多项式还是有留下来的
			if (NOISE)
				std::cout<<"selfadd： p1指向了最后一个数，但是p2看起来还有剩余的！ "<<std::endl;
			while(p2!=0 ) { //那就直到新鲜多项式全部扫光之前
				if(p1->exp>p2->exp) {
					if (NOISE)  std::cout<<"selfadd： p2指向： "<<p2->coe<<" "<<p2->exp<<std::endl;
					tailin( p2->coe,p2->exp);
					if (NOISE)	std::cout<<"selfadd：into tailin---";
					p2 = p2 ->next;
				}

			}
			if (NOISE)	std::cout<<"selfadd：终于填走了p2呼~ "<<std::endl;
		}
		if (NOISE)	{
			if(p2!=0 )std::cout<<"selfadd：将进入下一轮大大的while(p2!=0 )了，请坐稳 "<<std::endl;
			else std::cout<<"selfadd：终于填走了p2呼~~ *2"<<std::endl;
		}
	}
	if (NOISE)
		std::cout<<"selfadd：函数END "<<std::endl;
}

void pollist::deletepollist() { //删除它的时候我只是在删除一个个链表点
	polnode *p1=head;
	polnode *p2=head->next;//设前后指针，前面那个负责删，后面那个负责前进
	while(p2 !=0 ) { //当后面那个还没有扫完 所有项 的时候
		if (NOISE)
			std::cout<<p1->coe<<" "<<p1->exp<<" has deleted!---deletepollist\n";//显示前面那个
		delete p1;// 前面那个负责删
		p1 = p2;
		p2 = p2 ->next;// 后面那个负责前进，所以把后面那个指向的位置交给前面那个，准备下一轮再删，后面那个去前进吧！
	}//此时后面的指针已经扫完了全部的项，就剩尾巴没删除了
	if (NOISE)
		std::cout<<tail->coe<<" "<<tail->exp<<" (tail) has deleted!---deletepollist\n";//显示尾巴
	delete tail; //再见了尾巴
	head=tail=new polnode;
}

int main() {
	pollist p[2],pa,pm;

	for (int j=0; j<2; j++) {
		if (NOISE) std::cout<<j+1<<" main: into input()---";
		p[j].pollist::input();

		if (NOISE) std::cout<<j+1<<" main: echo: into output()---";
		if (NOISE)	p[j].pollist::output();
		if (NOISE)	std::cout<<std::endl;
	}

	pm.pollist::mul(p[0],p[1]);
	if (NOISE) std::cout<<"main: into mul()\n";
	pm.pollist::output();

	std::cout<<std::endl ;

	pa.pollist::add(p[0],p[1]);
	if (NOISE) std::cout<<"main: into add()\n";
	pa.pollist::output();

	return 0;
}

