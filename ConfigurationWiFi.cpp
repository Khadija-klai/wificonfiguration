#include "ConfigurationWiFi.hpp"

ConfigurationWiFi::ConfigurationWiFi() : server(80), apSSID("esp32"), apPassword("0123456789") {}

void ConfigurationWiFi::begin() {

  WiFi.mode(WIFI_STA); 
  WiFi.softAP(apSSID, apPassword, 1, 0, 1);
  pref.begin("wifiCredentials", false);
  ssidd = pref.getString("ssidKey", "");
  passwordd = pref.getString("pswdKey", "");
  pref.end();
  Serial.println(ssidd);
  Serial.println(passwordd);
  if (ssidd != "" && passwordd != "") {
    
    WiFi.begin(ssidd.c_str(), passwordd.c_str());
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10) {
      delay(1000);
      Serial.println("Connexion au WiFi en cours...");
      attempts++;
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connecté au WiFi avec succès");
    } else {
      Serial.println("Impossible de se connecter au WiFi. Activation du point d'accès.");
      WiFi.mode(WIFI_AP); 
       WiFi.softAP(apSSID, apPassword, 1, 0, 1);
    }
  } else {
    Serial.println("Aucune configuration WiFi enregistrée. Activation du point d'accès.");
    WiFi.mode(WIFI_AP); 
     WiFi.softAP(apSSID, apPassword, 1, 0, 1);
  }
  server.on("/", HTTP_GET, std::bind(&ConfigurationWiFi::handleRoot, this));
  server.on("/save", HTTP_POST, std::bind(&ConfigurationWiFi::handleSave, this));
  

  server.begin();
 
}

void ConfigurationWiFi::handleClient() {
    server.handleClient();
}

void ConfigurationWiFi::handleSave() {
 if (server.hasArg("ssid") && server.hasArg("password")) {
    // Récupération des valeurs saisies dans le formulaire
    String ssid = server.arg("ssid");
    String password = server.arg("password");
    pref.begin("wifiCredentials", false);
    pref.putString("ssidKey", ssid);
    pref.putString("pswdKey", password);
    pref.end();
    ssidd = ssid;
    passwordd = password;
    server.send(200, "text/plain", "Configuration sauvegardée. Redémarrez l'appareil pour appliquer les changements.");
    delay(1000);
    ESP.restart();
  } else {
    server.send(400, "text/plain", "Requête invalide : paramètres manquants.");
  }
}
void ConfigurationWiFi::handleRoot() {
 String html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css">
     <link href="https://fonts.googleapis.com/css2?family=Montserrat&display=swap" rel="stylesheet">
     <link rel="stylesheet" href="http://adresse_ip_de_votre_esp32/chemin_vers_votre_css_local/fontawesome.min.css">

    
    
    <title>Login landing page</title>
    <style>
@import url('https://fonts.googleapis.com/css?family=Raleway:400,700');

* {
	box-sizing: border-box;
	margin: 0;
	padding: 0;	
	font-family: Raleway, sans-serif;
}

body {
	background: linear-gradient(90deg, #C6D3F5,
#225CF0

	);		
}

.container {
	display: flex;
	align-items: center;
	justify-content: center;
	min-height: 100vh;
}

.screen {		
	background: linear-gradient(90deg, #1D39AB, #1D39AB);		
	position: relative;	
	height: 600px;
	width: 360px;	
	box-shadow: 0px 0px 24px #2138DE;
}

.screen__content {
	z-index: 1;
	position: relative;	
	height: 100%;
}

.screen__background {		
	position: absolute;
	top: 0;
	left: 0;
	right: 0;
	bottom: 0;
	z-index: 0;
	-webkit-clip-path: inset(0 0 0 0);
	clip-path: inset(0 0 0 0);	
}

.screen__background__shape {
	transform: rotate(45deg);
	position: absolute;
}

.screen__background__shape1 {
	height: 520px;
	width: 520px;
	background: #FFF;	
	top: -50px;
	right: 120px;	
	border-radius: 0 72px 0 0;
}

.screen__background__shape2 {
	height: 220px;
	width: 220px;
	background: #1D39AB;	
	top: -172px;
	right: 0;	
	border-radius: 32px;
}

.screen__background__shape3 {
	height: 540px;
	width: 190px;
	background: linear-gradient(270deg, #6D94E8, #1D39AB);
	top: -24px;
	right: 0;	
	border-radius: 32px;
}

.screen__background__shape4 {
	height: 400px;
	width: 200px;
	background: #1D39AB;	
	top: 420px;
	right: 50px;	
	border-radius: 60px;
}

.login {
	width: 320px;
	padding: 30px;
	padding-top: 156px;
}
/* Styles pour l'image */
.logo__image {
    max-width: 40%;
   
    display: block;
    margin: 0 auto;
    
    position: absolute;
    top: 110%; /* Positionner l'image au sommet du conteneur parent */
    left: 30%; /* Centrer l'image horizontalement */
    transform: translateX(-50%); /* Ajuster l'image pour la centrer correctement */
}


.login__field {
	padding: 20px 0px;	
	position: relative;	
}

.login__icon {
	position: absolute;
	top: 30px;
	color: #4066BD;
}

.login__input {
	border: none;
	border-bottom: 2px solid #D1D1D4;
	background: none;
	padding: 10px;
	padding-left: 24px;
	font-weight: 700;
	width: 75%;
	transition: .2s;
}

.login__input:active,
.login__input:focus,
.login__input:hover {
	outline: none;
	border-bottom-color: #153BD1;
}

.login__submit {
	background: #fff;
	font-size: 14px;
	margin-top: 30px;
	padding: 10px 20px;
	border-radius: 26px;
	border: 1px solid #D4D3E8;
	text-transform: uppercase;
	font-weight: 700;
	display: flex;
	align-items: center;
	width: 50%;
	color: #2C51BF;
	box-shadow: 0px 2px 2px #3B4DA8;
	cursor: pointer;
	transition: .2s;
}

.login__submit:active,
.login__submit:focus,
.login__submit:hover {
	border-color: #2955D9;
	outline: none;
}

.button__icon {
	font-size: 24px;
	margin-left: auto;
	color: #5271D1;
}
    </style>
</head>
<body>
 <div class="container">
	<div class="screen">
		<div class="screen__content">
		<div class="login__field">
			  <img src="data:image/png;base64,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"  class="logo__image">
		        </div>
			<form class="login" method="POST" action='/save'>
			
			 
		          
					<div class="login__field">
					<i class="login__icon fas fa-user"></i>
					<input type="text" class="login__input" id="ssid" name="ssid" placeholder="SSID">
				</div>
				<div class="login__field">
					<i class="login__icon fas fa-lock"></i>
					<input type="password" class="login__input" id="password" name="password" placeholder="Password">
				</div>
				<button class="button login__submit">
					<span class="button__text"> Connect</span>
					<i class="button__icon fas fa-chevron-right"></i>
				</button>				
			</form>
		</div>
		<div class="screen__background">
			<span class="screen__background__shape screen__background__shape4"></span>
			<span class="screen__background__shape screen__background__shape3"></span>		
			<span class="screen__background__shape screen__background__shape2"></span>
			<span class="screen__background__shape screen__background__shape1"></span>
		</div>		
	</div>
</div>

</body>
</html>

)rawliteral";
  server.send(200, "text/html", html);
}


