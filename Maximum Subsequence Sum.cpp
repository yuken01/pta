#include <iostream>
using namespace std;
int main() {
	long int k,n[10000];//kָʾ�����ж�������������̬����n[10000]�ᱻ����
	long int sum=0,sum2=0;// sum2�����ս�� �� sum�ǵ�ǰ�ۼƺ�
	long int s=0,e=0;// ��ǰ�ۼƺ͵�ͷβ��index
	long int s2=0,e2=0;
	int flag=1;
	long int flagi=0;
	cin>>k;//kָʾ�����ж������ᱻ����
	for(long int i=0; i<k; i++) { //����k����k��ѭ���������n[10000]��ȥ
		if (sum<0) {
			sum=0;//�����ǰ�ۼƺ�С���� ���Ǿ���0
			s=e=i; //��ͷ����
		}
		cin>>n[i];//�����n[i]��ȥ

		sum+=n[i];//���µ�ǰ�ۼƺ�
		e=i;
		if (n[i]==0&&flag!=0){
			flag=0;
			flagi=i;
		}
		if(sum2<sum) { //�Ƚ� ��ǰ�ۼƺ� �� ���ս����
			sum2=sum;//sum2��Զ������ ���е�ǰ�ۼƺ� ���ġ�
			s2=s;
			e2=e;
		}
	}//loop invariant: sum2 is always positively larger than sum and last sum2.
	cout<<sum2;// sum2�����ս��
	if(sum2)cout<<" "<<n[s2]<<" "<<n[e2];
	if(sum2==0&&flag)cout<<" "<<n[0]<<" "<<n[k-1];//������Ϊ�㣬flag==1��˵��ȫ���Ǹ�����������ͷ��ĩβ 
if(sum2==0&&flag==0)cout<<" "<<n[flagi]<<" "<<n[flagi];//������Ϊ�㣬flag==0��˵��ȫ���Ǹ�����0������0
}
