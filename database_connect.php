<?php
    // date_default_timezone_set('Europe/Paris');
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

    $connect = mysqli_connect($dbServername, $dbUsername, $dbPassword, $dbName);
?>