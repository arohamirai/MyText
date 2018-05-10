#零、 参考
boost.property_tree解析xml的帮助类以及中文解析问题的解决：https://www.cnblogs.com/qicosmos/p/3555668.html
http://www.technical-recipes.com/2014/using-boostproperty_tree/

# 一、包含头文件
···
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>
···

#二、功能实现
## 1. 读取.xml文件
···
	std:;string map_filepath = argv[1];
    boost::property_tree::ptree pt;
	try
	{
	boost::property_tree::read_xml(map_filepath, pt);	
	}
	catch(std::exception& e)
    {
        printf("Load %s map.xml failed!", map_filepath.c_str());
        return false;
    }
···

## 2. 获取关键字的数据
### 2.1 绝对路径获取
该方法必须保证.xml文件该关键字只出现过一次，也即没有重复，获取方法为：
···
// T 为关键字值的类型，Absolute_path为绝对路径，形为：根.节点1.节点2.<...>.属性名，例如map.property.node_count
T value = pt.get<T>("Absolute_path");
···
## 2.2 获取子元素
当一个关键字重复出现时，例如图书馆中用于记录所有书籍的.xml文件，<book>关键字个数会等于书的总数，获取所有书籍方法如下;
···
// 如果pt指向根节点
 boost::property_tree::ptree p_book_list = pt.get_child("根.book_list");
···
或者
···
// 如果pt本身就是子元素，假如book
p_book_list->second.get_child("book")
···
**说明：**
1. ptree维护了一个pair<string, ptree>的子节点列表，first指向的是该节点的TagName，second指向的才是ptree节点，因此在遍历ptree子节点时要注意迭代器的含义。
2. 推荐使用get_child_optional来访问，该接口可以判断是否存在要取的元素是否存在，不存在返回null, 存在返回boost::property_tree::ptree指针，定义时用auto