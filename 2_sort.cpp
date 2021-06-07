#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

void show(const vector<int> &nums){
    for(auto n:nums){
        cout<<n<<" ";
    }
    cout<<endl;
}
//插入排序
void Insertion_sort(vector<int> &nums){
    for(int i=1;i<nums.size();i++){
        int tmp=nums[i];
        int j=i-1;
        while(j>=0 && nums[j]>tmp){
            nums[j+1]=nums[j];
            j--;
        }
        nums[j+1]=tmp;
    }
}
//归并排序
void Merge(vector<int> &nums, vector<int> &tmp, int start,  int end){
    int mid=(start+end)>>1, i=start,j=mid+1, k=start;
    while(i<=mid || j<=end){
        if(j>end || (i<=mid && nums[i]<nums[j])) tmp[k++]=nums[i++];
        else tmp[k++]=nums[j++];
    }
    for(int index=start;index<=end;index++){
        nums[index]=tmp[index];
    }
}

void Merge_sort(vector<int> &nums, vector<int> &tmp,  int start,  int end){
    if(end==start)return;
    int mid=(start+end)>>1;
    Merge_sort(nums, tmp, start,mid);
    Merge_sort(nums, tmp, mid+1,end);
    Merge(nums,tmp,start,end);
}
123
int main(){
    vector<int> nums={5,2,4,6,1,3};
    // Insertion_sort(nums);
    vector<int> tmp=nums;
    Merge_sort(nums, tmp, 0,nums.size()-1);
    show(nums);

    return 0;
}
