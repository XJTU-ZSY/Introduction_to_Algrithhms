#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;
//背景：找出数组中和最大的子数组
struct NO4
{
    int low;
    int hight;
    int sum;
};
/***书中使用分治的方法：将数组分为两段，则和最大的子数组要么在其中一个子数组中，要么跨越两个子数组，据此可以写出主流程。时间复杂度为o(n*log(n))***/
//2.找出跨越两个子数组中的最大者：在断点处分别向两端求和，找到最大值。
NO4 find_crosssing_subarray(vector<int> &nums, int low, int hight){
    int mid=(low+hight)>>1;
    int left_sum=nums[mid],right_sum=nums[mid+1],sum1=left_sum,sum2=right_sum;
    NO4 tmp={mid,mid+1,sum1+sum2};
    for(int i=mid-1;i>=low;i--){
        left_sum+=nums[i];
        if(left_sum>sum1){
            sum1=left_sum;
            tmp.low=i;
        }
    }
    for(int i=mid+2;i<=hight;i++){
        right_sum+=nums[i];
        if(right_sum>sum2){
            sum2=right_sum;
            tmp.hight=i;
        }
    }
    tmp.sum=sum1+sum2;
    return tmp;
}
//1.主流程
NO4 find_maximum_subarray(vector<int> &nums, int low, int hight){
    if(hight==low)return {low,hight,nums[low]};
    int mid=(low+hight)>>1;
    NO4 left=find_maximum_subarray(nums,low,mid);
    NO4 right=find_maximum_subarray(nums,mid+1,hight);
    NO4 cross=find_crosssing_subarray(nums,low,hight);
    if(left.sum >=right.sum && left.sum >=cross.sum) return left;
    else if(right.sum >=left.sum && right.sum >=cross.sum) return right;
    else return cross;
}
/***leetcode上的方法，使用类似双指针，左指针作为子数组起点，右指针为终点，当子数组的和小于0时
左右指针移动到右指针的下一个位置并重新开始，否则记录子数组的和并和最大值比较。时间复杂度为o(n)***/
NO4 find_maxsum_subarray(vector<int> &nums){
    if(nums.size()==1)return {0,0,nums[0]};
    int tmp=nums[0],max=nums[0],left=0,right=0,j=0;
    for(int i=1;i<nums.size();i++){
        tmp+=nums[i];
        if(tmp>max){
            max=tmp;
            right=i;
            left=j;
        } 
        if(tmp<0){
            tmp=0;
            j=i+1;
        }
    }
    return  {left,right,max};
}

int main(){
    vector<int> nums={13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
    NO4 a=find_maximum_subarray(nums,0,nums.size()-1);
    cout<<a.low<<" "<<a.hight<<" "<<a.sum<<endl;
    NO4 max=find_maxsum_subarray(nums);
    cout<<max.low<<" "<<max.hight<<" "<<max.sum<<endl;
    return 0;
}