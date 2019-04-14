#include <iostream>

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
		//self-referential
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
				TailIn( coe1, exp1);
			}
		}

		void oup(polList& L1) {
			if (tail != 0) {
				for (polNode *tmp = head; tmp != tail; tmp = tmp->next) {
					if(tmp->coe)
						std::cout << tmp->coe << " "<<tmp->exp<< " ";
				}
				std::cout << tail->coe << " "<<tail->exp;
			} else std::cout<<0<< " "<<0;
		}

		polList& add(polList& L1,polList& L2) {
			polList L3;
			polNode *p1=L1.head;
			polNode *p2=L2.head;
			while(p1 !=0 && p2 !=0) {
				if(p1->exp=p2->exp)	{
					L3.TailIn((p1->coe+p2->coe),p1->exp);
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
			return L3;
		}

		polList& mul(polList& L1,polList& L2) {
			 polList L3;
			for(polNode *p1=L1.head; p1 !=0;	p1 = p1 ->next) {
				for(polNode *p2=L2.head; p2 !=0;	p2 = p2 ->next) {
					L3.CompIn(((p1->coe)*(p2->coe)),p1->exp+p2->exp);
				}
			}
			return L3;
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
				if (head == tail && head->exp >= exp1) {
					TailIn( coe1, exp1);//only 1 but can TailIn
				} else if (head == tail&& head->exp < exp1) { //only 1 and must headin
					head = new polNode( coe1, exp1,head);
				} else for (pred = head, tmp = head->next;
					            tmp != 0 && !(tmp->exp >= exp1);
					            pred = pred->next, tmp = tmp->next) { //more than 1
						if (tmp != 0) {
							pred->next = new polNode( coe1, exp1,tmp);
						} else TailIn( coe1, exp1);
					}
			} else TailIn( coe1, exp1);//empty then TailIn

		}

		polNode *head,*tail;
};


int main() {
	polList L[4];
	for(int i=0; i<2; i++) {
		int num;
		std::cin>>num;
		L[i].inp(num);
	}
	polList::L[2]=polList::add(polList::L1, polList::L2);
	polList::L[3]=polList::mul(polList::L1, polList::L2);
	oup(polList::L[3]);
	oup(polList::L[2]);
	return 0;
}

