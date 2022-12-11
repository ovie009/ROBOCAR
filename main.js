$(document).ready(function() {

    $(".car-buttons, .camera-buttons, .reset-camera").click(function() {

        let direction = this.dataset.direction; // get the direction data
        // console.log(direction);
        $.post("updateDb.php", {
            data: direction
        })

    })
});