#include <iostream>
using namespace std;
int main() {
	long int k,n[10000];//k指示究竟有多少输入数，静态数组n[10000]会被填充的
	long int sum=0,sum2=0;// sum2是最终结果 ， sum是当前累计和
	long int s=0,e=0;// 当前累计和的头尾的index
	long int s2=0,e2=0;
	int flag=1;
	long int flagi=0;
	cin>>k;//k指示究竟有多少数会被输入
	for(long int i=0; i<k; i++) { //根据k进行k次循环，输入填到n[10000]中去
		if (sum<0) {
			sum=0;//如果当前累计和小于零 ，那就置0
			s=e=i; //从头再来
		}
		cin>>n[i];//输入填到n[i]中去

		sum+=n[i];//更新当前累计和
		e=i;
		if (n[i]==0&&flag!=0){
			flag=0;
			flagi=i;
		}
		if(sum2<sum) { //比较 当前累计和 和 最终结果，
			sum2=sum;//sum2永远是正的 所有当前累计和 最大的。
			s2=s;
			e2=e;
		}
	}//loop invariant: sum2 is always positively larger than sum and last sum2.
	cout<<sum2;// sum2是最终结果
	if(sum2)cout<<" "<<n[s2]<<" "<<n[e2];
	if(sum2==0&&flag)cout<<" "<<n[0]<<" "<<n[k-1];//如果最后为零，flag==1，说明全都是负数，给出开头和末尾 
if(sum2==0&&flag==0)cout<<" "<<n[flagi]<<" "<<n[flagi];//如果最后为零，flag==0，说明全都是负数与0，给出0
}
