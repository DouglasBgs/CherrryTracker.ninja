# CherryTracker

[![ESP32 Build](https://github.com/DouglasBgs/CherrryTracker.ninja/actions/workflows/main.yml/badge.svg?branch=master&event=push)](https://github.com/DouglasBgs/CherrryTracker.ninja/actions/workflows/main.yml) [![License](https://img.shields.io/badge/license-MIT-red)](https://opensource.org/licenses/MIT)

##

## Sumário

1.  [**Introdução**](#Introducao)
    1.  [**Objetivo deste documento**](#Objetivo)
    2.  [**Escopo dos Hardwares do protótipo**](#Hardwares)
        1.  [**CherryTracker e seus principais componentes**](#componentes)
        2.  [**Missão da aplicação**](#missao)
    3.  [**Escopo dos Software do protótipo**](#software)
2.  [**Descrição geral do Protótipo**](#descricao)
3.  [**Requisitos do Sistema**](#requisitos)
    1.  [**Requisitos funcionais**](#funcional)
    2.  [**Requisitos não funcionais**](#nFuncional)
4.  [**Artefatos da Aplicação**](#artefatos)
    1.  [**Diagrama de arquitetura**](#arquitetura)
    2.  [**Diagrama de atividade**](#atividade)
    3.  [**Casos de Uso**](#casosUso)
        1. [**Descrição dos casos de uso**](#descCasosUso)
        2. [**Diagrama de casos de uso**](#diagramaCasosUso)
5.  [**Considerações Finais**](#consideracao)

##

<div id='Introducao'/>

> ## 1 Introdução

<div id='Objetivo'/>

> > #### 1.1 Objetivo deste documento
> >
> > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Neste documento são apresentado a especificação e evidências de implementação de um protótipo que é responsável por capturar dados de gps e imagens e armazená los, este protótipo foi nomeado de **CherryTracker**.
> > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Neste projeto temos o objetivo de aplicar os conceitos de FDD (Feature Driven Development) para o desenvolvimento do software, além de boas práticas de programação como o Clean Code.

<div id='Hardwares'/>

> > #### 1.2 Escopo dos Hardwares do protótipo

<div id='componentes'/>

> > > #### 1.2.1 CherryTracker e seus principais componentes
> > >
> > > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; **NEO-6M**: Responsável por captar e processar os dados de GPS, esse hardware consegue se conectar com sinal GPS, por meio de sua antena e é facilmente configurável, um dos seus principais pontos negativos é a potência de sua antena que não é capaz de atuar em ambientes fechados (sem exposição ao céu).
> > > >   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![NEO-6M](imgs/neo6m.png)
> > > >
> > > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; **ESP32**: Este dispositivo é responsável por processar os dados obtidos através do GPS e tratá-los. Este é um dispositivo com grande potencial, pois além de conter dois núcleos de processamento, possui também Bluetooth e WiFi integrados, isso possíbilita a criação de novas funcionalidades sem a necessidade da utilização de outros hardwares para conexão com os protocolos citados anteriormente.
> > > >   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![ESP32](imgs/esp32.jpg)
> > > >
> > > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; **ESP32-CAM**: Este dispositivo é responsável por gravar e armazenar todos os dados obtidos, pois conta com uma câmera e uma entrada para cartão micro SD. Embora sua câmera tenha pouca qualidade de resolução é possível troca-lá por outro módulo com qualidade de imagem superior.
> > > >
> > > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![ESP32](imgs/ESP32-CAM.png)

<div id='missao'/>

> > > #### 1.2.2 Missão da aplicação
> > >
> > > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Está aplicação tem o objetivo de facilitar o rastreamento de veículos, tendo em vista que existem muitas outras soluções que apenas gravam a localização do veículo em tempo real, esta é uma aplicação que além de localizar o veículo, também grava as imagens de todo o trajeto percorrido, facilitando a investigação de acidentes e outros problemas como desvio de rota e roubos, entre outros...
> > > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Com estas imagens será possível saber exatamente o momento em que o veículo estava em determinada localização através de um mapa, que mostrará todo seu trajeto percorrido.
> > > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; A aplicação não deve ficar limitada a estas funcionalidades, novas atualizações podem trazer integração com a internet ou até mesmo Bluetooth, facilitando a integração com o sistema web.

<div id='software'/>

> > #### 1.3 Escopo do Software do protótipo
> >
> > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Utilizadas a linguagem **c++** para o desenvolvimento deste projeto, embora o hardware permita a utilização da linguagem **python** para o seu desenvolvimento, optamos por utilizar c++ devido a sua grande gama de bibliotecas disponíveis para hardwares. As principais bibliotecas utilizadas neste projeto estão listadas abaixo:
> > >
> > > - [ArduinoJson](https://arduinojson.org/)
> > >   - Responsável por padronizar a comunicação serial entre as duas placas (esp32 e esp32cam).
> > > - [TinyGPS++](http://arduiniana.org/libraries/tinygpsplus/)
> > >   - Responsável por realizar a leitura e transformação dos dados capturados pelo gps (NEO-6M) e facilitar a manipulação dos dados.
> > > - [ESP32CamLib](https://github.com/DouglasBgs/ESP32CamLib)
> > >
> > >   - Biblioteca criada **exclusivamente** para este projeto, com o objetivo de gerenciar a filmagem e armazenamento do arquivo no cartão SD. Esta biblioteca foi desenvolvida a partir da necessidade e dificuldade de gerar e gravar vídeos utilizando linguagens de baixo nível.
> > >
> > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Para garantir que o código esteja funcionando corretamente foram implementados um workflow que garante o total funcionamento do código, pois nele é feito o build da aplicação e também faz a analise do código (lint).

<div id='descricao'/>

> ## 2 Descrição geral do Protótipo
>
> > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; O primeiro protótipo é um pequeno exemplo de funcionamento da aplicação, onde será feito a captura de dados do GPS e neste primeiro momento apenas a gravação de fotos no cartão SD, para que seja possível verificar se a integração entre todas as placas está ocorrendo como deveria.
> >
> > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; O segundo protótipo contará com a captura dos dados GPS como o primeiro protótipo porém contara com a gravação e armazenamento de vídeo.

<div id='requisitos'/>

> ## 3 Requisitos do Sistema

<div id='funcional'/>

> > #### 3.1 Requisitos funcionais
> >
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RF_001 O usuário não deve conseguir mexer no sistema.
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RF_002 O GPS deve estar sempre capturando e enviando dados para o controlador(ESP32).
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RF_003 O Sistema deve ser capaz de ligar automaticamente.
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RF_004 O sistema deve gravar os dados no cartão sd.
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RF_005 O sistema deve ascender um led sempre que o armazenamento estiver cheio.
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RF_006 O sistema deverá gravar a data e horário no nome do arquivo.

<div id='nFuncional'/>

> > #### 3.2 Requisitos não funcionais
> >
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RNF_001 O sistema não terá conexão coma a internet nem Bluetooth.
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RNF_002 O GPS deve se conectar ao ESP32.
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RNF_003 O Sistema deve permanecer ligado em StandBy.
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RNF_004 O sistema deve criptografar os dados armazenados.
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RNF_005 O GPS deve sempre ficar ligado.
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RNF_006 A câmera deve funcionar apenas com o veículo ligado.
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RNF_007 Plataforma de desenvolvimento: Arduino IDE.
> > > - &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; RNF_008 Linguagem de desenvolvimento C++.

<div id='artefatos'/>

> ## 4 Artefatos da Aplicação

<div id='arquitetura'/>

> > #### 4.1 Diagrama de arquitetura
> >
> > > - Neste diagrama é possível observar a conexão entre os dispositivos, onde a bateria representada na imagem abaixo deve ser a ligação com o sistema de bateria do veículo.
> > >   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![ESP32](imgs/arquitetura.png)

<div id='atividade'/>

> > #### 4.2 Diagrama de atividade
> >
> > > - Neste diagrama é possível observarmos o fluxo de atividades que será realizada por cada hardware presente no sistema e como cada uma das atividades dependem uma da outra para o correto funcionamento do sistema.
> > >   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![ESP32](imgs/atividade.png)

<div id='casosUso'/>

> > #### 4.3 Casos de Uso

<div id='descCasosUso'/>

> > > ##### 4.3.1 Descrição dos casos de uso
> > >
> > > > **Caso de uso 1:**
> > > > Nome: Ligar o veículo
> > > > Atores: Usuário
> > > > Prioridade: 3 essencial
> > > > Pré-condições: Ter bateria no veículo.
> > > > Fluxo do evento principal: O ator irá ligar o veículo dando início a gravação dos dados
> > > > Fluxo alternativo: Caso não seja obtidos dados do gps o programa não funcionará corretamente.
> > > >
> > > > **Caso de uso 2:**
> > > > Nome: Extrair Dados
> > > > Atores: Usuário
> > > > Prioridade: 3 essencial
> > > > Pré-condições: possuir dados no cartão SD.
> > > > Fluxo do evento principal: O ator irá remover o cartão SD do dispositivo para posteriormente visualizar as informações contidas nele.

<div id='diagramaCasosUso'/>

> > > ##### 4.3.2 Diagrama de casos de uso.
> > >
> > > &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![ESP32](imgs/caso_de_uso.png)

<div id='consideracao'/>

> ## 5 Considerações Finais
>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ///
