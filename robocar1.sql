-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Dec 21, 2022 at 07:33 AM
-- Server version: 10.4.25-MariaDB
-- PHP Version: 8.1.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+01:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `robocar`
--

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
(1, 'ROBOCAR_ADMIN', 'Robocar&@!%(*^#%$', '2022-12-21 06:46:03');

-- --------------------------------------------------------

--
-- Table structure for table `robocar_datastream`
--

CREATE TABLE `robocar_datastream` (
  `id` int(11) NOT NULL,
  `data` varchar(20) DEFAULT NULL,
  `datetime` datetime NOT NULL DEFAULT current_timestamp(),
  `mode` varchar(20) NOT NULL DEFAULT 'stream'
);

--
-- Dumping data for table `robocar_datastream`
--

INSERT INTO `robocar_datastream` (`id`, `data`, `datetime`, `mode`) VALUES
(1, 'car_right', '2022-12-12 23:02:50', 'stream');

--
-- Indexes for dumped tables
--

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
