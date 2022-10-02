# CherryTracker

---

> ## 1 Introdução

> > #### 1.1 Obejtivo deste documento

> > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Neste documento são apresentado a especificação e evidências de implementação de um protótipo que é responsável por capturar dados e armazená los, este protótipo foi nomeado de **CherryTracker**. Neste projeto temos o objetivo de aplicar os conceitos de FDD (Feature Driven Development) para o desenvolvimento do software, além de boas práticas de programação.

> > #### 1.2 Escopo dos Hardwares do protótipo

> > > #### 1.2.1 CherryTracker e seus principais componentes

> > > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; NEO-6M: Responsável por captar e processar os dados de GPS, esse hardware consegue se conectar com sinal GPS, por meio de sua antena e é facilmente configurável, um dos seus principais pontos negativos é a potência de sua antena que não é capaz de atuar em ambientes fechados (sem exposição ao céu).
> > > >   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![NEO-6M](imgs/neo6m.png)

> > > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ESP32: Este dispositivo é responsável por processar os dados obtidos através do GPS e tratá-los. Este é um dispositivo com grande potencial, pois além de conter dois núcleos de processamento, possui também bluetooth e wifi integrados.
> > > >   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![ESP32](imgs/esp32.jpg)

> > > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ESP32-CAM: Este dispositivo é reponsável por gravar e armazenar todos os dados obtidos, pois conta com uma câmera e uma entrada para cartão micro SD.

> > > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![ESP32](imgs/ESP32-CAM.png)
