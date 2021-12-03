Simulação de um programa de loja de ti, estou usando para aprender a escrever, ler, deletar e alterar arquivos. Tem 3 tipos de entradas, funcionários, produtos e fornecedores. Só implementei produto por enquanto (CRUD). O programa precisa da pasta "resource_files" para gravar os arquivos, por isso uma pasta vazia, vai sendo preenchida a medida que o uso acontece.

Cada entrada de produto é salva em um arquivo individual e um arquivo base salva todos os nomes de produtos, para usar quando precisar listar todos e pesquisar por nome. Nas duas ocasiões o programa itera pelo arquivo base de produto e procura o nome digitado ou simplesmente vai listando todos. O nome do arquivo é o nome do produto + .txt por isso a facilidade na hora de pesquisar. Verificar função makeFileName () para mais informações.

Fica tudo salvo em plain text, facilitando a leitura para debugar e testar (visto que é um programa direcionado para o aprendizado).
