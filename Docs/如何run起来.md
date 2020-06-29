一，方案使用的报表模块

<img src="https://github.com/seafitliu/data_statistic/blob/master/Docs/%E7%BB%9F%E8%AE%A1%E6%8A%A5%E8%A1%A8%E6%A8%A1%E5%9D%97.jpg">


(1) 可视化模块  Chart.js  基本上只需要了解数据的填充，非常简单
(2) 可视化数据获取模块  JQuery.js    做前端应该没有人不知道这个开源库了，HTTP调用也飞非常简单
(3) 数据JSON化HTTP服务模块  DST.StatisticServer  基于腾讯开源TARS的RPC服务
(4) RPC服务框架   腾讯开源TARS的RPC系统，有了这个，再大的流量也能轻松HOLD住，开发简单。
(5) MYSQL   待可视化数据存储容器，这个天下人皆知

二，详细步骤
 (1) 数据    数据库安装好后，建表 [表结构](https://github.com/seafitliu/data_statistic/blob/master/Docs/data_stat.sql)
