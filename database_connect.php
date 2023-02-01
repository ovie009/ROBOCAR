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

    // $dbServername = 'localhost';
    // $dbUsername = 'id20238456_robocar_admin';
    // $dbPassword = 'd9bSa3i]PTWEB((1';
    // $dbName = 'id20238456_robocar_stream';

    // $adminName = 'ROBOCAR_ADMIN';
    // $adminPassword = 'Robocar&@!%(*^#%$';

    $connect = mysqli_connect($dbServername, $dbUsername, $dbPassword, $dbName);
?>