CREATE TABLE `robocar`.`robocar_datastream` (`id` INT NOT NULL AUTO_INCREMENT , `car` VARCHAR(20) NOT NULL DEFAULT 'stop' , `camera` VARCHAR(20) NOT NULL DEFAULT 'center' , PRIMARY KEY (`id`)) ENGINE = InnoDB;

INSERT INTO `robocar_datastream` (`id`, `car`, `camera`) VALUES ('1', 'stop', 'center');

CREATE TABLE `robocar`.`login` (`id` INT NOT NULL AUTO_INCREMENT , `user` VARCHAR(20) NOT NULL DEFAULT 'ROBOCAR_ADMIN' , `password` VARCHAR(50) NOT NULL DEFAULT 'Robocar&@!%(*^#%$' , PRIMARY KEY (`id`)) ENGINE = InnoDB;

ALTER TABLE `robocar_datastream` CHANGE `car` `data` VARCHAR(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL, CHANGE `camera` `datetime` VARCHAR(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL DEFAULT CURRENT_TIMESTAMP;

ALTER TABLE `robocar_datastream` CHANGE `datetime` `datetime` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP;

ALTER TABLE `robocar_datastream` ADD `mode` VARCHAR(20) NOT NULL DEFAULT 'stream' AFTER `datetime`;