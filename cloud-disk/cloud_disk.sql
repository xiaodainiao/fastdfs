/*
Navicat MySQL Data Transfer

Source Server         : 阿里云
Source Server Version : 50719
Source Host           : 123.56.0.219:3306
Source Database       : cloud_disk

Target Server Type    : MYSQL
Target Server Version : 50719
File Encoding         : 65001

Date: 2017-10-25 00:22:30
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for file_info
-- ----------------------------
DROP TABLE IF EXISTS `file_info`;
CREATE TABLE `file_info` (
  `md5` varchar(200) NOT NULL,
  `file_id` varchar(256) NOT NULL,
  `url` varchar(512) NOT NULL,
  `size` bigint(20) DEFAULT NULL,
  `type` varchar(20) DEFAULT NULL,
  `count` int(11) DEFAULT NULL,
  PRIMARY KEY (`md5`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of file_info
-- ----------------------------

-- ----------------------------
-- Table structure for share_file_list
-- ----------------------------
DROP TABLE IF EXISTS `share_file_list`;
CREATE TABLE `share_file_list` (
  `user` varchar(128) NOT NULL,
  `md5` varchar(200) NOT NULL,
  `createtime` varchar(128) DEFAULT NULL,
  `filename` varchar(128) DEFAULT NULL,
  `pv` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of share_file_list
-- ----------------------------

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(128) NOT NULL,
  `nickname` varchar(128) NOT NULL,
  `password` varchar(128) NOT NULL,
  `phone` varchar(15) NOT NULL,
  `createtime` varchar(128) DEFAULT NULL,
  `email` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `uq_nickname` (`nickname`),
  UNIQUE KEY `uq_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=49 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user
-- ----------------------------

-- ----------------------------
-- Table structure for user_file_count
-- ----------------------------
DROP TABLE IF EXISTS `user_file_count`;
CREATE TABLE `user_file_count` (
  `user` varchar(128) NOT NULL,
  `count` int(11) DEFAULT NULL,
  PRIMARY KEY (`user`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user_file_count
-- ----------------------------

-- ----------------------------
-- Table structure for user_file_list
-- ----------------------------
DROP TABLE IF EXISTS `user_file_list`;
CREATE TABLE `user_file_list` (
  `user` varchar(128) NOT NULL,
  `md5` varchar(200) NOT NULL,
  `createtime` varchar(128) DEFAULT NULL,
  `filename` varchar(128) DEFAULT NULL,
  `shared_status` int(11) DEFAULT NULL,
  `pv` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user_file_list
-- ----------------------------
SET FOREIGN_KEY_CHECKS=1;
