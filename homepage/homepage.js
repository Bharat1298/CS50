document.getElementById('open-button').addEventListener("click", showMenu);
document.getElementById('close-button').addEventListener("click", hideMenu);

function showMenu(){
    document.getElementById("nav-links").style.right = "0px";
}

function hideMenu(button){
    document.getElementById("nav-links").style.right = "-200px";
}