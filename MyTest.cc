#include "MyTest.h"
#include "Person.pb.h"
#include "iostream"
using namespace std;

// 使用package的第一种解决方案用于解决报错
/* using namespace Dabing;
using namespace Erbing; */

// 第二种方法使用Person加入具体的package名
void MyTest::test()
{
    // 初始化
    Erbing::Person p;
    p.set_id(10);
    p.set_age(32);
    p.set_sex("man");
    // 这里演示数组效果
    p.add_name();
    p.set_name(0, "路飞");
    p.add_name("露西");
    p.add_name("艾斯");

    p.mutable_addr()->set_addr("北京市天安门");
    p.mutable_addr()->set_num(1001);
    p.set_color(Erbing::Color::Red);
    // 序列化对象p 最终得到一个字符串
    std::string output;
    p.SerializePartialToString(&output);

    // 要想看到protobuf中的数据，必须要将已经序列化好的protobuf对象进行反序列化操作
    // 反序列化
    Erbing::Person pp;
    pp.ParseFromString(output);
    cout << "p.id:" << pp.id();
    cout << ",sex:" << pp.sex() << endl;

    int size = pp.name_size();
    auto names = pp.mutable_name();
    names->Add("泰罗");
    //
    // 这里用*names表明mutable_name方法返回的是指向string数组容器的指针
    // 需要解引用表示为普通数组，才可用增强for循环遍历
    for (const auto &it : *names)
    {
        cout << "familys:" << it << endl;
    }
    cout << *(names->begin());
    // // 索引写法
    // for (int i = 0; i < size; ++i)
    // {
    //     cout << "familys:" << pp.name(i) << endl;
    // }
    cout << ",age:" << pp.age();
    cout << ",addr:" << pp.addr().addr();
    cout << ",num:" << pp.addr().num();
    cout << ",color:" << pp.color() << endl;
}