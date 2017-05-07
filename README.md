# 42sh : Chell

## Features:

**Edition de ligne:**

    -edition simple en multiligne
    -Selection            : ALT + Fleche
    -Copier/Coller        : ALT + C ALT + V
    -Couper               : ALT + X
    -Debut de ligne       : HOME
    -Fin de ligne         : END
    -Deplacement par mots : SHIFT + Fleche G/D
    -Deplacement par ligne: SHIFT + Fleche H/B

**Built In:**
```
-Echo
-Hash
-Exit
-Setenv
-Unsetenv
-Export
-unset
-Local
-Cd
-Read
-History
```

**Autre :**

```
Redirection                  : >   >>  <<  <  <<<   |
Separateur                   :  ;
Operateur                    : &&  ||
Variable Locales             : unset et export
Historique                   : History et !
Backquote                    : `
Recherche dans l'historique  : CTRL + R
inhibiteurs                  :  "   '
Subshell                     : (  )
Gestion CTRL + C et CTRL + D
Autocompletion dynamique
Gestion des File descriptor

```

## Bonus:

**Commande :**
```
            - Aperture
            - Patate
```

## Shellscript
<pre>
if CONDITION
COMMAND

if CONDITION
do COMMAND1
COMMAND2
COMMAND3
...
done

if CONDITION
do
COMMAND1
COMMAND2
COMMAND3
...
done
</pre>

<pre>
while CONDITION
COMMAND

while CONDITION
do COMMAND1
COMMAND2
COMMAND3
...
done

while CONDITION
do
COMMAND1
COMMAND2
COMMAND3
...
done
</pre>

<pre>
for VAR in STRING1 STRING2 STRING3 ...
COMMAND

for VAR in STRING1 STRING2 STRING3 ...
do COMMAND1
COMMAND2
COMMAND3
...
done

for VAR in STRING1 STRING2 STRING3 ...
do
COMMAND1
COMMAND2
COMMAND3
...
done
</pre>

**Conditions**

<pre>
string        True if string is not the null string.
-z string     True if the length of string is zero.
s1 = s2       True if the strings s1 and s2 are identical.
s1 != s2      True if the strings s1 and s2 are not identical.
s1 < s2       True if string s1 comes before s2 based on the ASCII value of their characters.
s1 > s2       True if string s1 comes after s2 based on the ASCII value of their characters.
n1 -eq n2     True if the integers n1 and n2 are algebraically equal.
n1 -ne n2     True if the integers n1 and n2 are not algebraically equal.
n1 -gt n2     True if the integer n1 is algebraically greater than the integer n2.
n1 -ge n2     True if the integer n1 is algebraically greater than or equal to the integer n2.
n1 -lt n2     True if the integer n1 is algebraically less than the integer n2.
n1 -le n2     True if the integer n1 is algebraically less than or equal to the integer n2.
</pre>
