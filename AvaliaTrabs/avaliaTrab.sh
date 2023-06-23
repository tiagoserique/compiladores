
EXEMPLOS="Exemplo5 Exemplo7.01 Exemplo7.02 Exemplo7.03 Exemplo7.04 Exemplo7.05 Exemplo8.05 Exemplo8.06 Exemplo8.07 Exemplo8.08 Exemplo8.09 Exemplo8.10 ExemploErro1 ExemploErro2"


echo "Usage: avaliaTrab.sh <arquivo executavel compilador"
echo "Avalia: Para os primeiros quatro erros, meio ponto por erro."
echo "Avalia: Para os demais, um ponto por erro."

for exemplo in $EXEMPLOS; do
    echo -n $exemplo "... "
    cp $exemplo/pgma.pas .
    cp $exemplo/MEPA MEPA-Res

    $1 pgma.pas > res
    diff MEPA MEPA-Res  -bBty
done

