-- phpMyAdmin SQL Dump
-- version 4.6.5.2
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 24-11-2017 a las 20:00:37
-- Versión del servidor: 10.1.21-MariaDB
-- Versión de PHP: 7.1.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `clase_php`
--

DELIMITER $$
--
-- Procedimientos
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `REGISTRO` (IN `fechaIN` DATE)  NO SQL
select codigo,count(fecha) as cantidad,max(hora) AS MAXIMO,(SELECT tac,hora FROM `camilla` where fecha='2017-11-22' order by hora DESC LIMIT 1) as tac from camilla where fecha=fechaIN GROUP by codigo$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `admin`
--

CREATE TABLE `admin` (
  `id` int(11) NOT NULL,
  `user` varchar(15) NOT NULL,
  `pw` varchar(165) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `admin`
--

INSERT INTO `admin` (`id`, `user`, `pw`) VALUES
(1, 'usu1', '$2y$10$4ZNsjtQQHXpD1Gq.hSTBZOlaR4MyVySyGsIleqyGzLx.TQMAdwjCK');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `camilla`
--

CREATE TABLE `camilla` (
  `idCam` int(3) NOT NULL,
  `codigo` int(2) NOT NULL,
  `fecha` date NOT NULL,
  `hora` int(6) DEFAULT NULL,
  `tac` int(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `camilla`
--

INSERT INTO `camilla` (`idCam`, `codigo`, `fecha`, `hora`, `tac`) VALUES
(55, 1, '2017-11-17', 153114, 1),
(56, 1, '2017-11-17', 153224, 2),
(57, 1, '2017-11-17', 153239, 2),
(58, 1, '2017-11-17', 153305, 1),
(59, 1, '2017-11-17', 153327, 1),
(60, 1, '2017-11-17', 153339, 1),
(61, 1, '2017-11-17', 153358, 1),
(62, 1, '2017-11-17', 153404, 1),
(63, 1, '2017-11-22', 2803, 1),
(64, 1, '2017-11-22', 2813, 2),
(65, 1, '2017-11-22', 2832, 2),
(66, 1, '2017-11-22', 2843, 1),
(67, 1, '2017-11-22', 3058, 1),
(68, 1, '2017-11-22', 3105, 2),
(69, 1, '2017-11-22', 3147, 1),
(70, 1, '2017-11-22', 3153, 2),
(71, 1, '2017-11-22', 3308, 1),
(72, 1, '2017-11-22', 3318, 2),
(73, 1, '2017-11-22', 3332, 2),
(74, 1, '2017-11-22', 3344, 1),
(75, 1, '2017-11-22', 3354, 1),
(76, 1, '2017-11-22', 3404, 2),
(77, 1, '2017-11-22', 3425, 2),
(78, 1, '2017-11-22', 3438, 1),
(79, 1, '2017-11-24', -4259, 1),
(80, 1, '2017-11-24', -4246, 2),
(81, 1, '2017-11-24', -4184, 2),
(82, 1, '2017-11-24', -4166, 2),
(83, 1, '2017-11-24', -4144, 2),
(84, 1, '2017-11-24', 17, 2),
(85, 1, '2017-11-24', 209, 2),
(86, 1, '2017-11-24', 313, 2),
(87, 1, '2017-11-24', 519, 2),
(88, 1, '2017-11-24', 1147, 2),
(89, 1, '2017-11-24', 1242, 2),
(90, 1, '2017-11-24', 1402, 2),
(91, 1, '2017-11-24', 1808, 2),
(92, 1, '2017-11-24', 2045, 2),
(93, 1, '2017-11-24', 2508, 1),
(94, 1, '2017-11-24', 2559, 1),
(95, 1, '2017-11-24', 2608, 1),
(96, 1, '2017-11-24', 2617, 1),
(97, 1, '2017-11-24', 2810, 1),
(98, 1, '2017-11-24', 2904, 1),
(99, 1, '2017-11-24', 2914, 1),
(100, 1, '2017-11-24', 3038, 2),
(101, 1, '2017-11-24', 3111, 2),
(102, 1, '2017-11-24', 3127, 2),
(103, 1, '2017-11-24', 3157, 2),
(104, 1, '2017-11-24', 3344, 1),
(105, 1, '2017-11-24', 3353, 1),
(106, 1, '2017-11-24', 3744, 2),
(107, 1, '2017-11-24', 12638, 1),
(108, 1, '2017-11-24', 12653, 1),
(109, 1, '2017-11-24', 21131, 1),
(110, 1, '2017-11-24', 21139, 1),
(111, 1, '2017-11-24', 21147, 1),
(112, 1, '2017-11-24', 21406, 1),
(113, 1, '2017-11-24', 34739, 1),
(114, 1, '2017-11-24', 34747, 1),
(115, 1, '2017-11-24', 34802, 1),
(116, 1, '2017-11-24', 34931, 1),
(117, 1, '2017-11-24', 34944, 1),
(118, 1, '2017-11-24', 35006, 1),
(119, 1, '2017-11-24', 35743, 1),
(120, 1, '2017-11-24', 35804, 1),
(121, 1, '2017-11-24', 40129, 1),
(122, 1, '2017-11-24', 40308, 1),
(123, 1, '2017-11-24', 42316, 1),
(124, 1, '2017-11-24', 42333, 1),
(125, 1, '2017-11-24', 42420, 1),
(126, 1, '2017-11-24', 42702, 1),
(127, 1, '2017-11-24', 42736, 1),
(128, 1, '2017-11-24', 42900, 1),
(129, 1, '2017-11-24', 42936, 1),
(130, 1, '2017-11-24', 43238, 1),
(131, 1, '2017-11-24', 43638, 1),
(132, 1, '2017-11-24', 43646, 1),
(133, 1, '2017-11-24', 62813, 1),
(134, 1, '2017-11-24', 62845, 1),
(135, 1, '2017-11-24', 63404, 1),
(136, 1, '2017-11-24', 63958, 1),
(137, 1, '2017-11-24', 64246, 1),
(138, 1, '2017-11-24', 64310, 1),
(139, 1, '2017-11-24', 64316, 1),
(140, 1, '2017-11-24', 64330, 1),
(141, 1, '2017-11-24', 64347, 1),
(142, 1, '2017-11-24', 64451, 1),
(143, 1, '2017-11-24', 64510, 1),
(144, 1, '2017-11-24', 64556, 1),
(145, 1, '2017-11-24', 64642, 1),
(146, 1, '2017-11-24', 64657, 1),
(147, 1, '2017-11-24', 131922, 2),
(148, 1, '2017-11-24', 132033, 2),
(149, 1, '2017-11-24', 132055, 2),
(150, 1, '2017-11-24', 141305, 2),
(151, 1, '2017-11-24', 141311, 2),
(152, 1, '2017-11-24', 141324, 2),
(153, 1, '2017-11-24', 141759, 2);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `camilla`
--
ALTER TABLE `camilla`
  ADD PRIMARY KEY (`idCam`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `admin`
--
ALTER TABLE `admin`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT de la tabla `camilla`
--
ALTER TABLE `camilla`
  MODIFY `idCam` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=154;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
