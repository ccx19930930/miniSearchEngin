#基于文本检索的轻量化搜索引擎

#目录结构：

miniSearchEngin
|--README.md
|--server
|	|--Makefile
|	|--bin
|	|--conf
|		\...                         与头文件文件夹相同的目录结构
|	|--data
|	|--include
|	|	|--Cache                     缓存头文件文件夹
|	|	|--CppJieba                  开源库CppJieba头文件文件夹
|	|	|--Dictionary                Trie字典树头文件文件夹
|	|	|--Query_module              查询模块头文件文件夹
|	|	|--server                    服务器头文件文件夹
|	|	|--tcp                       Socket头文件文件夹
|	|	|--thread_pool               线程池头文件文件夹
|	|	\--Timer                     计时器头文件文件夹
|	\--src
|		\...                         与头文件文件夹相同的目录结构
|--WebDataBase
|	|--Makefile
|	|--bin
|	|--conf
|		\...                         与头文件文件夹相同的目录结构
|	|--data
|	|	|--delete.sh                 删除结果的脚本
|	|	|--go.sh                     执行可执行性文件的脚本，与上一个脚本同为测试时使用
|	|	|--Dictionary.json           用Trie字典树存储的倒排索引
|	|	|--Offset.json               网页偏移库
|	|	|--Ripepage.lib              网页库
|	|	|--rss                       存放rss源
|	|	\--test                      存放中间文件，如分组情况、词频情况等
|	|--include
|	|	|--CppJieba                  开源库CppJieba头文件文件夹
|	|	|--Dictionary                Trie字典树头文件文件夹
|	|	|--PageLib                   总头文件文件夹
|	|	|--root                      对象语义头文件文件夹
|	|	\--rss                       网页库相关处理头文件文件夹
|	\--src
|		\...                         与头文件文件夹相同的目录结构
\--client                            测试客户端



#离线部分	WebDataBase

1、网页去重前进行分组，分组依据为最高词频前20个词的首字节按位异或的结果。测试时共有约400多编文章，一共分出了100多组，然后进行组内比较最高词频的词的方法进行去重，使得每篇文章进行比较的平均次数为4次，比暴力比较减少了100倍。
2、倒排索引表存在Trie字典树中，同时字典树提插入、查找、联想、导入、导出、遍历等功能。

#在线部分	server

1、每个线程都拥有一个缓存，并有一个总缓存。计时器每过一个周期，都进行备份与同步。
2、子缓存采用队列结构。
3、同步时，先将每个子缓存的数据拷入总缓存，同时进行去重处理，然后将总缓存的数据拷回子缓存。在拷回子缓存时，子缓存不可用，查询模块直接访问总缓存，但是此时不住缓存中写入数据，以保证无缝连接。
4、reactor + threadpool模式

#共用部份

1、Trie字典树
2、开源库CppJieba
3、开源库Jsoncpp
4、开源库TinyXml2
5、开源库Boost.Regex

#后续待更改

1、用Redis替换现有的缓存系统
2、使用开源库log4cpp记录日志
3、使用MySql存储离线数据
4、服务器改用开源库muduo
