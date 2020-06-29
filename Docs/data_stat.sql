-- MySQL dump 10.13  Distrib 5.5.62, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: data_statistic
-- ------------------------------------------------------
-- Server version	5.5.62-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `data_statistic`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `data_statistic` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `data_statistic`;

--
-- Table structure for table `tb_statistic`
--

DROP TABLE IF EXISTS `tb_statistic`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_statistic` (
  `axis_x` varchar(100) NOT NULL COMMENT 'X轴',
  `axis_y` bigint(20) unsigned NOT NULL COMMENT '数据字段值',
  `dataset_name` varchar(100) NOT NULL COMMENT '数据集名称',
  `category` varchar(200) NOT NULL COMMENT '数据字段分类',
  `sub_category` varchar(200) NOT NULL COMMENT '数据字段子分类',
  PRIMARY KEY (`axis_x`,`dataset_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_statistic`
--

LOCK TABLES `tb_statistic` WRITE;
/*!40000 ALTER TABLE `tb_statistic` DISABLE KEYS */;
INSERT INTO `tb_statistic` VALUES ('20200618',3503187,'pv','ios',''),('20200618',5503187,'pv_android','android',''),('20200618',503145,'uv','ios',''),('20200618',1503987,'uv_android','android',''),('20200619',3516987,'pv','ios',''),('20200619',5516987,'pv_android','android',''),('20200619',513325,'uv','ios',''),('20200619',1512254,'uv_android','android',''),('20200620',3508794,'pv','ios',''),('20200620',5508794,'pv_android','android',''),('20200620',506187,'uv','ios',''),('20200620',1495874,'uv_android','android',''),('20200621',3789547,'pv','ios',''),('20200621',5789547,'pv_android','android',''),('20200621',503145,'uv','ios',''),('20200621',1589741,'uv_android','android',''),('20200622',3698741,'pv','ios',''),('20200622',5698741,'pv_android','android',''),('20200622',523891,'uv','ios',''),('20200622',1579856,'uv_android','android',''),('20200623',3956870,'pv','ios',''),('20200623',5956870,'pv_android','android',''),('20200623',563387,'uv','ios',''),('20200623',1604587,'uv_android','android',''),('20200624',4099841,'pv','ios',''),('20200624',6099841,'pv_android','android',''),('20200624',538451,'uv','ios',''),('20200624',1854110,'uv_android','android',''),('20200625',4136547,'pv','ios',''),('20200625',6136547,'pv_android','android',''),('20200625',596845,'uv','ios',''),('20200625',1987456,'uv_android','android','');
/*!40000 ALTER TABLE `tb_statistic` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-06-29  7:27:32
