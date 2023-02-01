-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Feb 01, 2023 at 10:12 PM
-- Server version: 10.4.25-MariaDB
-- PHP Version: 8.1.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `robocar`
--

-- --------------------------------------------------------

--
-- Table structure for table `ip`
--

CREATE TABLE `ip` (
  `id` int(99) NOT NULL,
  `address` varchar(20) DEFAULT NULL,
  `datetime` datetime NOT NULL DEFAULT current_timestamp()
);

--
-- Dumping data for table `ip`
--

INSERT INTO `ip` (`id`, `address`, `datetime`) VALUES
(1, '192.168.235.43', '2023-01-23 10:46:00');

-- --------------------------------------------------------

--
-- Table structure for table `login`
--

CREATE TABLE `login` (
  `id` int(11) NOT NULL,
  `user` varchar(20) NOT NULL DEFAULT 'ROBOCAR_ADMIN',
  `password` varchar(50) NOT NULL DEFAULT 'Robocar&@!%(*^#%$',
  `datetime` datetime NOT NULL DEFAULT current_timestamp()
);

--
-- Dumping data for table `login`
--

INSERT INTO `login` (`id`, `user`, `password`, `datetime`) VALUES
(1, 'ROBOCAR_ADMIN', 'Robocar&@!%(*^#%$', '2023-01-30 21:24:17');

-- --------------------------------------------------------

--
-- Table structure for table `robocar_datastream`
--

CREATE TABLE `robocar_datastream` (
  `id` int(11) NOT NULL,
  `data` varchar(20) DEFAULT NULL,
  `datetime` datetime NOT NULL DEFAULT current_timestamp(),
  `motion_detected` int(1) NOT NULL DEFAULT 0,
  `flash` int(1) NOT NULL DEFAULT 0,
  `mode` varchar(20) NOT NULL DEFAULT '''STREAM''',
  `tolerance` varchar(20) NOT NULL DEFAULT '''AVERAGE''',
  `esp8266_timestamp` datetime NOT NULL DEFAULT current_timestamp(),
  `servo_angle` int(3) NOT NULL DEFAULT 90
);

--
-- Dumping data for table `robocar_datastream`
--

INSERT INTO `robocar_datastream` (`id`, `data`, `datetime`, `motion_detected`, `flash`, `mode`, `tolerance`, `esp8266_timestamp`, `servo_angle`) VALUES
(1, 'captured_image', '2023-01-23 10:41:24', 0, 0, 'STREAM', 'LOW', '2023-01-23 01:19:10', 90);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `ip`
--
ALTER TABLE `ip`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `login`
--
ALTER TABLE `login`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `robocar_datastream`
--
ALTER TABLE `robocar_datastream`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `ip`
--
ALTER TABLE `ip`
  MODIFY `id` int(99) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `login`
--
ALTER TABLE `login`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `robocar_datastream`
--
ALTER TABLE `robocar_datastream`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
