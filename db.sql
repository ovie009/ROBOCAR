CREATE TABLE `robocar`.`robocar_datastream` (`id` INT NOT NULL AUTO_INCREMENT , `car` VARCHAR(20) NOT NULL DEFAULT 'stop' , `camera` VARCHAR(20) NOT NULL DEFAULT 'center' , PRIMARY KEY (`id`)) ENGINE = InnoDB;

INSERT INTO `robocar_datastream` (`id`, `car`, `camera`) VALUES ('1', 'stop', 'center');