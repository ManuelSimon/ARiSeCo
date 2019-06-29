Traballando con contedores Singularity
====

Creando contedores inmutábeis: simg
----

`singularity build ubuntu_latest.simg bootstrap_min.def`

O arquivo de bootstrap é igual que o empregado pra facer bootstrap normal.

Creando contedores mutábeis
----

### ext3

`sudo singularity build --writable ubuntu_latest.img bootstrap_min.def`

**Ollo**: É posíbel que a máquina non recoñeza o formato ext3 e polo tanto non poida empregar esta clase de contedores.

### Contedor cartafol: sandbox

`sudo singularity build --sandbox ubuntu_latest bootstrap_min.def`

Lanzando unha shell interactiva
----

### contedores arquivo

`singularity shell ubuntu_latest.simg`

### contedores cartafol

`sudo singularity shell --writable ubuntu_latest`

A idea é entrares nunha shell interactiva nos contedores cartafol, que son mutábeis, e logo facer un cambio de formato a simg.

Lanzando instancias
----

**Listando instancias:** 

`singularity instance list`

**Lanzando instancias:**

`singularity instance start ubuntu_latest.simg ubuntu`

**Entrando na shell dunha instancia:**

`singularity shell instance://ubuntu`

**Parando instancias:**

`singularity instance.stop ubuntu`
