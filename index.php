<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Robocar</title>
    <link rel="stylesheet" href="style.css">
    <link rel="shortcut icon" href="/clutch.png" type="image/x-icon">
</head>
<body>
    <nav>
        Robocar 
    </nav>
    <div class="videostream">
        <p>
            <em>VIDEOSTREAM</em>
        </p>
        <div class="camera_control">
            <form action="updateDb.php" method="GET" class="camera_form">
                <input type="hidden" value="left" name="camera">
                <button type="submit" class="camera-buttons">
                    <span class="left_arrow"></span>
                </button>
            </form>
            <form action="updateDb.php" method="GET"  class="camera_form">
                <input type="hidden" value="right" name="camera">
                <button type="submit" class="camera-buttons">
                    <span class="right_arrow"></span>
                </button>
            </form>
        </div>
    </div>
    <div class="car_control">
        <div class="controller_center">

            <form action="updateDb.php" method="GET" class="car_unassigned">
                <input type="hidden" value="unassigned" name="car">
                <button type="submit">
                    C
                </button>
            </form>

            <form action="updateDb.php" method="GET" class="car_forward">
                <input type="hidden" value="forward" name="car">
                <button type="submit" class="car-buttons">
                    <span class="up-arrow"></span>
                </button>
            </form>
            
            <form action="updateDb.php" method="GET" class="car_backward">
                <input type="hidden" value="backward" name="car">
                <button type="submit" class="car-buttons">
                    <span class="down-arrow"></span>
                </button>
            </form>
            
            <form action="updateDb.php" method="GET" class="car_right">
                <input type="hidden" value="right" name="car">
                <button type="submit" class="car-buttons">
                    <span class="right-arrow"></span>
                </button>
            </form>
            
            <form action="updateDb.php" method="GET" class="car_left">
                <input type="hidden" value="left" name="car">
                <button type="submit" class="car-buttons">
                    <span class="left-arrow"></span>
                </button>
            </form>
            
        </div>
    </div>
</body>
</html>