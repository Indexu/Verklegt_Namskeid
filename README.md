# Verklegt Námskeið 1 2015. 
## Hópur 57




  



##### Skilaverkefni 1


Fyrstu skilaverkefnið okkar var að búa til forrit sem heldur utan um lista af fólki ásamt öðrum frekari upplýsingum um þau. 
Gagnagrunnurinn var vistaður í textaskrá person.txt svo allar upplýsingar voru til staðar, jafnvel þó svo að slökkt væri á forritinu. 
Við útfærðum forritið þannig að notandi gæti skráð þekktar persónur úr sögu tölvunarfræðinnar, inn í gagnagrunninn.  

Við völdum að hafa eftirfarandi gögn um hverja persónu: 


* Nafn
* Kyn 

* Fæðingardag

* Dánardag (ef það á við)

* Upprunaland  
  


Við útfærðum gagnagrunninn á þann veg að hægt værir að leita í honum í öllum ofantöldum dálkum og að auki þegar gagnagrunnurinn er birtur er í boði að stjórna því
hvernig hann er raðaður, þ.e. í hækkandi eða lækkandi röð. Við notuðumst við lagskipta hönnun við útfærslu gagnagrunnsins og notuðum QT Creator við útfærsluna. 
Við notuðumt líka við Github.com til að hýsa gagnagrunninn og veittum skósveinum okkar, Snævari og Sigurgrími aðganga að honum. Þátttaka hópameðlima var í allastaði 
mjög jöfn og við unnum þetta samt mest í sameiningu á tvær tölvur að öllu jafna.



##### Kynning 

Við héldum rosalega flotta kynningu. Það voru engar spurningar í lok kynningar og allir voru 
massa sáttir í framsetninguna. Við skiptum þessu bróðurlega á milli okkar, Aron og Svanur kynntu virkni forritsins og Haukur sat við tölvuna og sýndi allar skipanir 
sem kynntar 
voru á skjávarpanum í rauntíma. Hann bætti við einstaklingi í gagnagrunninn, breytti honum og eyddi honum svo út. Því næst sýndu Haukur og Hilmar salnum kóðann við 
gríðarlegar undirtektir þeirra sem fylgdust með.



##### Skilaverkefni 2
Annað skilaverkefnið okkar var að færa gagnagrunninn í SQLite sem er viðbót við Modzilla Firefox svo engin frekari uppsentningar var þurfi. Við 
lásum gagnagrunninn okkar í upphafi yfir í SQL með forlykkju svo við þyrftum ekki að slá hvern einstkling handvirkt inn. Svo flæktust málin aðeins og við bættum við 
dálknum machines og svo tengingum á milli person og machine allur gagnagrunnurinn er nú vistaður sem verklegt.sqlite. Allar skipanir sem notast var við í 
skilaverkefni 1 héldu sér en svo útfærðum við þetta aðeins öðruvísi í skilaverkefni 2 þó svo að grunnhugmyndin sé sú sama.  
Eftirfarandi gögn voru notuðu í 
skilaverkefni 2:


* Nafn persónu

* Kyn 
* Fæðingardag

* Dánardag (ef það á við)

* Vélarnafn
* Byggingarár

* Hvort vélin var byggð
* Vélartýpa

* Vélarkerfi

* Upprunarland  



Við bættum líka við tengingum á milli persóna og tölva sem og að geta skoðað hver margar tölvu tengjast hverri persónu og öfugt ásamt því að geta leitað í tengingunum.