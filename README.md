# CherryTracker

---

> ## 1 Introdução
>
> > #### 1.1 Obejtivo deste documento
> >
> > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Neste documento são apresentado a especificação e evidências de implementação de um protótipo que é responsável por capturar dados e armazená los, este protótipo foi nomeado de **CherryTracker**. Neste projeto temos o objetivo de aplicar os conceitos de FDD (Feature Driven Development) para o desenvolvimento do software, além de boas práticas de programação.
> >
> > #### 1.2 Escopo dos Hardwares do protótipo
> >
> > > #### 1.2.1 CherryTracker e seus principais componentes
> > >
> > > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; NEO-6M: Responsável por captar e processar os dados de GPS, esse hardware consegue se conectar com sinal GPS, por meio de sua antena e é facilmente configurável, um dos seus principais pontos negativos é a potência de sua antena que não é capaz de atuar em ambientes fechados (sem exposição ao céu).
> > > >   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![NEO-6M](imgs/neo6m.png)
> > > >
> > > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ESP32: Este dispositivo é responsável por processar os dados obtidos através do GPS e tratá-los. Este é um dispositivo com grande potencial, pois além de conter dois núcleos de processamento, possui também bluetooth e wifi integrados.
> > > >   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![ESP32](imgs/esp32.jpg)
> > > >
> > > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ESP32-CAM: Este dispositivo é reponsável por gravar e armazenar todos os dados obtidos, pois conta com uma câmera e uma entrada para cartão micro SD.
> > > >
> > > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![ESP32](imgs/ESP32-CAM.png)
> > >
> > > #### 1.2.2 Missão da aplicação
> > >
> > > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Está aplicação tem o objetivo de facilitar o rastreamento de veículos, tendo em vista que existem muitas outras soluções que apenas gravam a localização do veículo em tempo real, esta é uma aplicação que além de localizar o veículo, também grava as imagens de todo o trajeto percorrido, facilitando a investigação de acidentes e outros problemas como desvio de rota e roubos, entre outros...
> > > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Com estas imagens será possível saber exatamente o momento em que o veículo estava em determinada localização através de um mapa, que mostrará todo seu trajeto percorrido.
>
> ## 2 Descrição geral do Protótipo
>
> > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; O primeiro protótipo é um pequeno exemplo de funcionamento da aplicação, onde será feito a captura de dados do GPS e neste primeiro momento apenas a gravação de fotos no cartão SD, para que seja possível verificar se a integração entre todas as placas está ocorrendo como deveria.
> > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Após os primeiros testes executando o
