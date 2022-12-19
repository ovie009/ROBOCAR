<?php
    
    $dbServername = 'localhost';
    $dbUsername = 'root';
    $dbPassword = '';
    $dbName = 'robocar';
    
    // $dbServername = 'localhost';
    // $dbUsername = 'id20021735_robocar_admin';
    // $dbPassword = 'Robocar@2021';
    // $dbName = 'id20021735_robocar';

    // $adminName = 'ROBOCAR_ADMIN';
    // $adminPassword = 'Robocar&@!%(*^#%$';

    // $dbServername = 'sql213.epizy.com'; // host
    // $dbUsername = 'epiz_33020133'; // user
    // $dbPassword = 'rher9e3c38YnB'; // password
    // $dbName = 'epiz_33020133_robocar'; // database name

    $connect = mysqli_connect($dbServername, $dbUsername, $dbPassword, $dbName);
?>