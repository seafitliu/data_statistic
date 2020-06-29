一，方案使用的报表模块

<img src="https://github.com/seafitliu/data_statistic/blob/master/Docs/%E7%BB%9F%E8%AE%A1%E6%8A%A5%E8%A1%A8%E6%A8%A1%E5%9D%97.jpg">


(1) 可视化模块  Chart.js  基本上只需要了解数据的填充，非常简单
(2) 可视化数据获取模块  JQuery.js    做前端应该没有人不知道这个开源库了，HTTP调用也飞非常简单
(3) 数据JSON化HTTP服务模块  DST.StatisticServer  基于腾讯开源TARS的RPC服务
(4) RPC服务框架   腾讯开源TARS的RPC系统，有了这个，再大的流量也能轻松HOLD住，开发简单。
(5) MYSQL   待可视化数据存储容器，这个天下人皆知

二，详细步骤
 (1) 数据    数据库安装好后，建表 [建表语句](https://github.com/seafitliu/data_statistic/blob/master/Docs/data_stat.sql)  我灌了一部分数据，作为例子
         表字段  
         axis_x（X轴数据，比如UV统计，X轴就是日期）
         axis_y（Y轴数据，一般数据具体的数值了，比如UV统计，一般是UV数据）
         dataset_name （数据集的名称，比如我们要在可视化图表上同时显示UV和PV，那么UV和PV分别是两个不同的数据集）
         category和sub_category  （为了支持大型统计数据时，可能需要对数据进行大的分类，比如IOS和ANDROID就是大的分类，sub_category则是为了更大的分类。二次开发时，这里可以自定义使用或者不使用）
 
 
 (2) HTTP服务  
      这一步，可以完全用其他方案替换，不过为了将来大流量支撑，建议从一开始就找一个HOLD满全场的框架，这样就不用频繁的对服务进行改造了。
      1，TARS安装  详见<https://github.com/TarsCloud/Tars>  具体就不多说了
      2，编译和安装DST.StatisticServer    代码见[StatServer]<https://github.com/seafitliu/data_statistic/tree/master/StatServer>目录 TARS框架安装后之后，直接在目录make， 然后会生成StatisticServer.tgz，直接发布到TARS框架里即可，注意这个是HTTP服务，务必按照TARS框架的规范来，对于完全不了解TARS服务的人来说，可能会有一些障碍，不过把TARS学习到位了，也会很容易。有问题可以微信我。
      3，数据JSON化     将从数据库拿到的axis_x，axis_y， dataset_name填到JSON串里  root[data[i]["dataset_name"]][data[i]["axis_x"]] = data[i]["axis_y"]; 

 (3) 数据可视化WEB  
