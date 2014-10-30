* If counstructor throws exception memory is freed. 
* Two methods can exactly be the same except for the constness.
* Use is_class<T>() to find out if it is class . You used this in multiple questions 
* declval can't be used openly, can only be used in context of decltype and sizeof and other unevaluated operands 
* has to use typename iterator_traits<iterator>::iterator_category blah to use it. don't know why 
* When making a struct with template, and if you are doing template specialization. Then there has to be a base type. You can't have only specializations, even if that means having the base type empty struct.