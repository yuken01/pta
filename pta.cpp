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

		int coe,exp;
		polNode *next;
		//self-referential
};



class polList{
public:
//interface 	
void inp(int num)
//input from screen and get a linked list (Tai)
void oup(polList)const
//output to screen
add

mul
//data

head
tail
private:
TailIn
//insert from tail
CompIn	
//compare then insert(Tai)
}pol1, pol2, pol3, pol4;
 
