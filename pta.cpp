#include <iostream>
#include <fstream>
int main() {
	class polNode {
// for nodes of the list
		public:
			polNode() {
				next = 0;
			}
			//constructor#1
			polNode(int coe1,int exp1, polNode *ptr = 0) {
				coe	=coe1;
				exp	=exp1;
				next = ptr;
			}
			//constructor#2
			int coe,exp;
			polNode *next;
			//a self-referential pointer
	};



	class polList {
		public:

			polList() {
				head = tail = 0;
			}

			void inp(int num) {
				for(int i=0; i<num; i++) {
					int coe1,exp1;
					std::cin>>coe1>>exp1;

					//	ifstream::inFile>>coe1>>exp1;
					TailIn( coe1, exp1);
				}
			}

			void oup() {
				if (tail != 0) {
					for (polNode *tmp = head; tmp != tail; tmp = tmp->next) {
						if(tmp->coe)
							std::cout << tmp->coe << " "<<tmp->exp<< " ";
					}
					if(tail->coe) std::cout << tail->coe << " "<<tail->exp;
				} else std::cout<<0<< " "<<0;
			}

			void add(polList& L1,polList& L2,polList& L3) {

				polNode *p1=L1.head;
				polNode *p2=L2.head;
				while(p1 !=0 && p2 !=0) {
					if(p1->exp==p2->exp)	{
						L3.TailIn((p1->coe)+(p2->coe),p1->exp);
						p1 = p1 ->next;
						p2 = p2 ->next;
					} else if(p1->exp>p2->exp) {
						L3.TailIn((p1->coe),p1->exp);
						p1 = p1 ->next;
					} else {
						L3.TailIn((p2->coe),p2->exp);
						p2 = p2 ->next;
					}
				}
				if(p1 !=0) {
					L3.TailIn((p1->coe),p1->exp);
					p1 = p1 ->next;
				}
				if(p2 !=0) {
					L3.TailIn((p2->coe),p2->exp);
					p2 = p2 ->next;
				}

			}

			void mul(polList& L1,polList& L2, polList& L3) {
				int i=0;
				for(int *p1=L1.head; p1 !=0;	p1 = p1 ->next,i++) {
					for(int *p2=L2.head; p2 !=0;	p2 = p2 ->next) {
						L3.CompIn(((p1->coe)*(p2->coe)),p1->exp+p2->exp);
						std::cout<<i;
					}
				}
			}


		private:
			void TailIn(int coe1,int exp1) {//insert from tail
				if (tail != 0) {
					// only if list not empty;
					tail->next = new polNode( coe1, exp1);
					tail = tail->next;
				} else head = tail = new polNode(coe1, exp1);
			}



			void CompIn(int coe1,int exp1) {//compare then insert
				polNode *pred, *tmp;
				if (head != 0) {                    // if non-empty list;
					if (head == tail && (head->exp) > exp1) {
						TailIn( coe1, exp1);//only 1 but can TailIn
						std::cout<<coe1<<""<<exp1<<std::endl;
					} else if (head == tail&& (head->exp) < exp1) { //only 1 and must headin
						head = new polNode( coe1, exp1,head);
						std::cout<<coe1<<""<<exp1<<std::endl;
					} else if(head == tail&& (head->exp) == exp1) {//only 1 but the same exp
						head->coe += coe1;
						std::cout<<coe1<<""<<exp1<<std::endl;
					} else  if(head != tail) {//more than 1

						for (pred = head, tmp = head->next;
						        tmp != 0 && (tmp->exp >= exp1);
						        pred = pred->next, tmp = tmp->next) { //
							if (tmp != 0 && ((pred->exp) > exp1)) {
								pred->next = new polNode( coe1, exp1,tmp);
								std::cout<<coe1<<""<<exp1<<std::endl;
							} else if(tmp != 0 && ((pred->exp)== exp1)) {
								pred->coe+=coe1;
								std::cout<<coe1<<""<<exp1<<std::endl;
							} else if(tmp==0) {
								TailIn( coe1, exp1);
								std::cout<<coe1<<""<<exp1<<std::endl;
							}
						}
					} else {
						TailIn( coe1, exp1);   //empty then TailIn

						std::cout<<coe1<<exp1<<std::endl;
					}

				}
			}

			polNode *head,*tail;
	};



	polList L[4];
	for(int i=0; i<2; i++) {
		int num;
		std::cin>>num;
		L[i].polList::inp(num);
	}/*
	ifstream inFile;
	inFile.std::open("input.txt");
	if (!inFile.std::is_open()) // failed to open file

	{
		std::cout << "Could not open the file " << filename << std::endl;
		std::cout << "Program terminating.\n";
	}
	for(int i=0; i<2; i++) {
		int num;
		inFile>>num;
		L[i].polList::inp(num);
	}
	if (inFile.std::eof())
		std::cout << "End of file reached.\n";
	else if (inFile.std::fail())
		std::cout << "Input terminated by data mismatch.\n";
	else
		std::cout << "Input terminated for unknown reason.\n";
	inFile.std::close();
*/
	L[2].polList::add(L[0],L[1],L[2]);
	L[3].polList::mul(L[0],L[1],L[3]);
	L[3].polList::oup();
	std::cout<<std::endl;
	L[2].polList::oup();

	return 0;
}
//下次我一定用动态数组
//20190415fail again 类与对象掌握不牢靠，导致mul与CompIn可能因为基本常识
	//，如数据类型不对总是出错。  
//先写高数作业和概率作业吧 ，写完了再重新学起cpp
//概率准备一本正式作业本和首次草稿本，高数同理 
//cpp的语言和算法挺难学的，说真的，一个是语言，一个是思想，准备要点本子和自我编程草稿本吧 

