#include <iostream>
class Test {
    int id;
   public:

    Test(int _id) : id(_id){std::cout <<"Construction " <<id<< std::endl;}
    ~Test(){std::cout <<"Destruction " <<id << std::endl;}
    void test(){
        if(id)
            delete this;
    }

};


int main(int argc, char ** argv)
{
  Test * t1 = new Test(1);

    t1->test();


  return 0;
}
