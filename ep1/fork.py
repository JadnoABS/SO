import os

# Cria um processo filho
filho = os.fork()


# No processo pai: filho == id do fork
# No processo filho: filho == 0

if(filho > 0):
    # Executa no processo pai
    print("Hello World do pai")
else:
    # Executa no processo filho
    print("Hello World do filho")
