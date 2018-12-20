#include <iostream>
using namespace std;

template <typename T>  
struct TraitsHelper {  
    typedef T ret_type;  
    typedef T par_type;  
};
template <>  
struct TraitsHelper<int> {  
    typedef int ret_type;  
    typedef int par_type;  
};  
template <>  
struct TraitsHelper<float> {  
    typedef float ret_type;  
    typedef float par_type;  
};

template <typename T>  
class Test {  
public:  
    typename TraitsHelper<T>::ret_type Print(typename TraitsHelper<T>::par_type d);   
};

template <typename T>
typename TraitsHelper<T>::ret_type Test<T>::Print(typename TraitsHelper<T>::par_type d)
{
	cout << d << endl;
	return d;
}

int main()
{
	int i = 1;
	float j = 0.5;

	Test<int> test1;
	test1.Print(i);

	Test<float> test2;
	test2.Print(j);
}