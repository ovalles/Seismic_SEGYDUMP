=======

######
SEGYDUMP
######

*Segy headers file manipulation toolkit in C*

=======


**Main Features**

* Segy header manipulation from terminal

.. contents:: **Table of Contents**
    :local:
    :backlinks: none

============
Installation
============

-----
Linux
-----

    ::

    $ github clone   


*************
Prerequisites
*************

Make sure you have gcc compiler.


*******
Install
*******

Download the latest version from `GitHub`_. If you have ``git`` installed, you can use the following command:

.. _GitHub: https://github.com/ovalles

::

$ git clone https://github.com/ovalles/Seismic_SEGYDUMP.git

Finally, enter the newly created directory containing the source code and run:

::

$ cd ./01_DISPLAY_HEADERS
$ gcc -o Display_TrcHeaders Display_TrcHeaders.c
$ ./Display_TrcHeaders file.sgy MaxNumberOfTracesInFile | more


===========
Screenshots
===========

#.. image:: https://github.com/ovalles/Seismic_SEGYDUMP/blob/master/80_SCREENSHOTS/01_DisplayTrcHeaders.png

.. image:: http://img.youtube.com/vi/bvje_Nt8wic/0.jpg
   :target: https://www.youtube.com/watch?v=bvje_Nt8wic&list=PL7t3mNvsiYoadSfsYG618LIlzkGzGqAf7

.. image:: https://github.com/ovalles/Seismic_SEGYDUMP/blob/master/80_SCREENSHOTS/02_DisplayTrcHeaders.png

=======
License
=======

Licensed under the `GPLv3`_ license.

.. _GPLv3: http://www.gnu.org/licenses/gpl-3.0.html

=======
Authors
=======

`Asdrubal Ovalles`_ 

.. _Asdrubal Ovalles: https://www.linkedin.com/in/asdr%C3%BAbal-ovalles-8401a352

Made in Venezuela, 2016

=======

==========
References
==========

.. [1] SeGY Rev 1.0
=======



