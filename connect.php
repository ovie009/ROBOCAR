<html>
<body>

<?php

$dbname = 'epiz_33020133_robocar'; // database name
$dbuser = 'epiz_33020133'; // user
$dbpass = 'rher9e3c38YnB'; // password
$dbhost = 'sql213.epizy.com'; // host

// $con=mysqli_connect("sql213.epizy.com","epiz_33020133","rher9e3c38YnB","epiz_33020133_robocar");// server, user, password, database


$connect = mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);

if(!$connect){
	echo "Error: " . mysqli_connect_error();
	exit();
}

echo "Connection Success!<br><br>";

$temperature = $_GET["data"];

$query = "INSERT INTO `testwifi` (`value`) VALUES ('John Jones');";

$result = mysqli_query($connect,$query);

echo "Insertion Success!<br>";

?>
</body>
</html>