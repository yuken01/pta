#include <iostream>
#define NOISE 0
class polnode {//ÿ���㶼��ϵ��ָ��,��ָ����һ�����ָ��
	public:
		int coe , exp ;
		polnode * next ;
		polnode() {
			coe=0;
			exp=0;
			polnode * next=0;
			if (next!=0)std::cout<<"polnode(): (next!=0)\n";

		}
		polnode(int c,int e) {//Ĭ�ϵĻ�ָ�����0��ָ��ϵ�� ��Ϊ0
			coe=c;
			exp=e;
			polnode * next=0;
			if (next!=0)std::cout<<"polnode(int c,int e): (next!=0)\n";
		}
};
class pollist {//��ÿһ������ʽ����һ��ͷβָ��
	private:
		polnode *head ,*tail;
		void selfadd(pollist & t1);
		void tailin(int c,int e);
		void deletepollist();
	public:
		pollist() {//ÿ���´�����pollistͷβָ�붼��ͬ����ϵ������ָ��
			head=tail=new polnode(0,0);
		}
		void input();
		void output();
		void mul(pollist & L1,pollist & L2);
		void add(pollist & L1,pollist & L2);
};
void pollist::tailin(int c,int e) {

	polnode *temp= new polnode(c,e);//����ط��������캯����nextΪ�㣬ȴ���ص������ʱ������next��Ϊ�㣬��������������ָ����
	if (NOISE)	if (temp->next!=0)	std::cout<<"tailin: new temp->next!=0\n";
	tail->next=temp;// ����β��
	tail=temp;//�������µ�β����
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
	int flag=1;//����ú�������1��Ȼ����,��ζ��һ��if(tmp->coe)Ҳû�н��룬�������ʽ����ÿ����ϵ������0
//	if (NOISE)	std::cout<<"\noutput:�ʼ��flag "<<flag<<std::endl;
	for (polnode* tmp = head->next; tmp != 0; tmp = tmp->next) {//������ͷ�Ŀձ���ÿ����
		if(tmp->coe) { //�������ϵ��Ϊ�����
			if (flag!=1)
				std::cout<< " " <<tmp->coe << " "<<tmp->exp;
			if (flag==1) {
				std::cout << tmp->coe << " "<<tmp->exp;//�����һϵ��������
				++flag; //flag��1�����2�� flag���˼����ǲ���ȫ0����м�����Ƿ��һϵ�������������
//				if (NOISE)	std::cout<<"\noutput:��һϵ���������++flag;  flag "<<flag<<std::endl;
			}
		}
	}
	if(flag==1) {
		std::cout<<"0 0";//�������ʽ����ÿ����ϵ������0
//		if (NOISE)	std::cout<<"flag "<<flag<<std::endl;
	}
	if (NOISE)	std::cout<<"output: end "<<std::endl;
}
void pollist::add(pollist & L1,pollist & L2) {
	polnode *p1=L1.head->next;	//��һ��������������ֱ������ȥ
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
	polnode *p1=L1.head->next;//��һ��������������ֱ������ȥ,��ѭ���ѳ�ʼ��
	pollist t1;
	while(p1 !=0  ) {//�����ʽ������ȫ֮ʱ��������
		if (NOISE)
			std::cout<<"mul: �ѽ�����ѭ��while(p1 !=0  )֮�� "<<std::endl;
		if (NOISE)
			std::cout<<"mul: ��ʱ��ѭ�� "<<p1->coe<<" "<<p1->exp<<std::endl;
		polnode *p2=L2.head->next;//��һ��������������ֱ������ȥ,ÿ����ѭ�����ᾭ����ѭ����ʼ��
		if (NOISE)
			std::cout<<"mul: ��ѭ�����Ͻ�����ѭ��,��p2ָ��ָ��ͷ���� "<<std::endl;
		while(p2 !=0) { //	�ڶ���ʽ������ȫ֮ʱ��������
			if (NOISE)
				std::cout<<"mul: �ѽ�����ѭ��while(p2 !=0  )֮�� "<<std::endl;
			if (NOISE)
				std::cout<<"mul: ��ʱ��ѭ�� "<<p2->coe<<" "<<p2->exp<<std::endl;
			int c =p1->coe * p2->coe ;// ����ϵ�����
			int e =p1->exp + p2->exp ;// ����ָ�����
			if (p1==L1.head->next) {
				tailin(c,e);//��������״���ѭ����ֱ������ٻ����method�Ķ���ʽpm��
				if (NOISE)
					std::cout<<"mul:�״���ѭ������ʱ��ѭ������ˣ� "<<tail->coe<<" "<<tail->exp<<std::endl;
			} else {
				t1.tailin(c,e);//�������t1����һ����ѭ�������ڱ�����ѭ������֮ǰ�ӵ�pm����
				if (NOISE)
					std::cout<<"mul:���״���ѭ��������ѭ������ʱ��ѭ��t1���ڱ���ˣ����ӣ� "
					         <<t1.tail->coe<<" "<<t1.tail->exp<<std::endl;
			}
			p2 = p2 ->next;
			if (NOISE)
				if(p2!=0 )
					std::cout<<"mul: ������һ����ѭ��  while(p2 !=0  )֮�� "<<std::endl;
			if (NOISE)
				if(p2==0 )
					std::cout<<"mul: ��ѭ�� ���~ "<<std::endl;
		}
		if (p1!=L1.head->next) {
			if (NOISE)
				std::cout<<"mul:���״���ѭ������������ѭ���Լӻ��ڣ� "<<std::endl;
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
				std::cout<<"mul: ��������һ����ѭ���ˣ������� "<<std::endl;
			else if(p1==0 )
				std::cout<<"mul: ��ѭ�� ���~ "<<std::endl;
		}
	}
}
//���� mul����������ʽ��ˣ���һ��������������ֱ������ȥ�������㷨���ǵ�һ����ʽÿһ��͵ڶ�����ʽ�������
//����ѭ���ɵ����飩�õ������ж���ʽ�ӵ��ٻ����method�Ķ���ʽ�������Ͼ��ǽ������ѭ���ɵ����飩��
//�⺯��������Ƕ��ѭ�����״���ѭ����ֱ������ٻ����method�Ķ���ʽ��
//�Ժ�ÿ����ѭ����ʼһ�ֶ����Եõ�һ������������õ����ʶ���ʽ��������ѭ������������
//������ѭ���ӽ�β����ʱ�򣬾ͻ�ӵ�������
//��������������Ķ���ʽ����һ����ѭ�����������
void pollist::selfadd(pollist & t1) { //�������ʽ�Ļ�ĳ���ϵ�ָ��ͨ�����������Ǹ���Ӧλ�����ָ��Ҫ��
	polnode *p1=head->next;
	polnode *p2=t1.head->next;//��һ��������������ֱ������ȥ
	if (NOISE)
		std::cout<<"selfadd�� �����p1ָ�� "<<p1->coe<<" "<<p1->exp<<std::endl;
	if (NOISE)
		std::cout<<"selfadd�� �����p2ָ�� "<<p2->coe<<" "<<p2->exp<<std::endl;
	while(p2!=0 ) { //Ŀ���ǰ����ʶ���ʽ��ȫ�����������ʽ��ȥ
		if (p1 !=tail) {
			if((p1->exp > p2->exp)&&(p1->next->exp < p2->exp)) {
				//����deǰһ�����ָ�������ʶ���ʽ��ָ��Ҫ�����һ��С
				if (NOISE)
					std::cout<<"selfadd�� ǰ���С֮�� "<<std::endl;
				polnode* temp=new polnode(p2->coe,p2->exp);//�����µ������
				temp->next=p1->next;//�ɺ���ǰ�����������Ե�next������ָ��
				p1->next=temp;//����Ϊ�ǵ�������nextָ�������һ���ڵ㣬������ǰ���󻹵ñ����һ���ĵ�ַ

				p1=p1->next;//������������ָ����ԭ�����ʶ���ʽ���ģ����Խ��������ʼ����
				if (NOISE)
					if(p1!=0 )
						std::cout<<"selfadd�� ���������µ�p1ָ�� "<<p1->coe<<" "<<p1->exp<<std::endl;
				p2 = p2 ->next;
				if (NOISE)
					if(p2!=0 )
						std::cout<<"selfadd�� ���������µ�p2ָ�� "<<p2->coe<<" "<<p2->exp<<std::endl;
			}

			else if((p1->exp > p2->exp)&&(p1->next->exp == p2->exp)) { //ǰһ���������ָ�������ʶ���ʽ��ָ��Ҫ�����һ������
				if (NOISE)
					std::cout<<"selfadd�� ǰ����֮�� "<<std::endl;
				p1=p1->next;//�������ʽָ��͵�ָ���Ǹ�ָ����ͬ���
				p1->coe += p2->coe ;//�������ˣ�ֱ��ϵ����һ�¾Ϳ�����
				if (NOISE)
					if(p1!=0 )
						std::cout<<"selfadd�� �µ�p1ָ�� "<<p1->coe<<" "<<p1->exp<<std::endl;
				p2 = p2 ->next;
				if (NOISE)
					if(p1!=0 )
						if(p2!=0 )std::cout<<"selfadd�� �µ�p2ָ�� "<<p2->coe<<" "<<p2->exp<<std::endl;
			}// ���������Ϳ��Բ��������ʶ���ʽ�����ٿ��ǣ�ָ����ƶ���

			else if((p1->exp > p2->exp)&&(p1->next->exp > p2->exp)) { //ǰһ���������ָ�������ʶ���ʽ��ָ��Ҫ�����һ��Ҳ��
				p1=p1->next;//�������ʽָ��͵�����Ų������һ��ѭ�����ǿ���������������أ�
				if (NOISE)
					std::cout<<"selfadd�� ǰ����֮�� "<<std::endl;
				if (NOISE)
					if(p1!=0 )
						std::cout<<"selfadd�� �µ�p1ָ�� "<<p1->coe<<" "<<p1->exp<<std::endl;
				if (NOISE)
					if(p1!=0 )
						std::cout<<"selfadd�� p2ָ�򲻱䰡~�� "<<p2->coe<<" "<<p2->exp<<std::endl;
			}
			if (p1 ==tail)
				if (NOISE)
					std::cout<<"selfadd�� p1ָ�������һ������ "<<std::endl;
		}

		if(p1==tail&&p2!=0 ) { //����������ʽȫɨ�������ʶ���ʽ��������������
			if (NOISE)
				std::cout<<"selfadd�� p1ָ�������һ����������p2����������ʣ��ģ� "<<std::endl;
			while(p2!=0 ) { //�Ǿ�ֱ�����ʶ���ʽȫ��ɨ��֮ǰ
				if(p1->exp>p2->exp) {
					if (NOISE)  std::cout<<"selfadd�� p2ָ�� "<<p2->coe<<" "<<p2->exp<<std::endl;
					tailin( p2->coe,p2->exp);
					if (NOISE)	std::cout<<"selfadd��into tailin---";
					p2 = p2 ->next;
				}

			}
			if (NOISE)	std::cout<<"selfadd������������p2��~ "<<std::endl;
		}
		if (NOISE)	{
			if(p2!=0 )std::cout<<"selfadd����������һ�ִ���while(p2!=0 )�ˣ������� "<<std::endl;
			else std::cout<<"selfadd������������p2��~~ *2"<<std::endl;
		}
	}
	if (NOISE)
		std::cout<<"selfadd������END "<<std::endl;
}

void pollist::deletepollist() { //ɾ������ʱ����ֻ����ɾ��һ���������
	polnode *p1=head;
	polnode *p2=head->next;//��ǰ��ָ�룬ǰ���Ǹ�����ɾ�������Ǹ�����ǰ��
	while(p2 !=0 ) { //�������Ǹ���û��ɨ�� ������ ��ʱ��
		if (NOISE)
			std::cout<<p1->coe<<" "<<p1->exp<<" has deleted!---deletepollist\n";//��ʾǰ���Ǹ�
		delete p1;// ǰ���Ǹ�����ɾ
		p1 = p2;
		p2 = p2 ->next;// �����Ǹ�����ǰ�������԰Ѻ����Ǹ�ָ���λ�ý���ǰ���Ǹ���׼����һ����ɾ�������Ǹ�ȥǰ���ɣ�
	}//��ʱ�����ָ���Ѿ�ɨ����ȫ�������ʣβ��ûɾ����
	if (NOISE)
		std::cout<<tail->coe<<" "<<tail->exp<<" (tail) has deleted!---deletepollist\n";//��ʾβ��
	delete tail; //�ټ���β��
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

