SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for IR commands
-- ----------------------------
DROP TABLE IF EXISTS `commands`;
CREATE TABLE `commands` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `protocol` binary(4) DEFAULT NULL,
  `address` binary(2) DEFAULT NULL,
  `command` binary(2) DEFAULT NULL,
  `name` varchar(9) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=961 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
