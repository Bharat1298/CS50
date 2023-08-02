document.getElementById('home').onClick = tabs();

function tabs(){
    var home = document.getElementById("header");
    home.classList.toggle("active");
}