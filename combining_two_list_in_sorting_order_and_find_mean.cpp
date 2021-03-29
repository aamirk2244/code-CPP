#include  <iostream>
void print(int *p, int length)
{
    std::cout << "printing the combined List " << std::endl;
    std::cout << "[ ";
    for(int i = 0 ; i< length; i++)
    {
        std::cout << p[i] << " ";
    }
    std::cout << "]";
    std::cout << std::endl;
}
void Median(int *list, int length)
{
    //if middle value is even than then median will have two values
    if(length % 2 == 0)std::cout <<"Median is " <<  list[int(length/2)-1] << " and "<< list[int(length/2)] << std::endl;
    else std::cout << "Median is " << list[int(length/2)] << std::endl;
    // if medain is odd than the median will have 1 value
}
int* combine_two_sorted_list_in_sorting_order(int *l1, int *l2, int l1_length, int l2_length)
{
    
    int total_length = l1_length + l2_length;
    int *l3 = new int[total_length];
    int index_l3 =  0;
    int index_l1 = 0;
    int index_l2 = 0;
    for(int i = 0 ; i < total_length; i++)
    {
        if (index_l1 >= l1_length && index_l2 < l2_length)
        {
            l3[index_l3] = l2[index_l2];
            index_l2++;
            index_l3++;

        }
        else if(index_l2 >= l2_length && index_l1 < l1_length)
        {
            l3[index_l3] = l1[index_l1];
            index_l1++;
            index_l3++;

        }
        else
        {
            if (l1[index_l1] < l2[index_l2])
            {
                l3[index_l3] = l1[index_l1];
                index_l3++;
                index_l1++;

            }
            else
            {
                l3[index_l3] = l2[index_l2];
                index_l3++;
                index_l2++;
            }

        }
    }
    print(l3, total_length);
    return l3;
}
int main()
{
    int l1[] = {80, 85, 86, 87,100}; 
    int l2[] = {2, 60, 69, 70,86};
    int total_size = sizeof(l1)/sizeof(int) + sizeof(l2)/sizeof(int);
    int *l3 = combine_two_sorted_list_in_sorting_order(l1, l2,sizeof(l1)/sizeof(int),sizeof(l2)/sizeof(int));
    Median(l3, total_size);
}