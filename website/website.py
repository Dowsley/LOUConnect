from flask import *
from AVL import *
app = Flask(__name__)

@app.route("/")
@app.route("/signup")
def signup():
    return render_template('signup.html', title='Sign Up')

@app.route("/signup-tags")
def signupTags():
    return render_template('signup-tags.html', title='Sign Up - Tags')

@app.route("/signup-describe")
def signupDescribe():
    return render_template('signup-describe.html', title='Sign Up - Describe')

@app.route("/profile")
def profile():
    nome = "Joao Dowsley"
    arvore = None
    arvore = desserializar(arvore)
    found = buscarNo(arvore, nome)

    if found!=None:
        f_nome = found.nome
        f_cpf = found.cpf
        f_ocup = found.ocupacao
        f_email = found.email
        f_dia = found.niver.dia
        f_mes = found.niver.mes
        f_ano = found.niver.ano
        f_desc = found.desc
    else:
        f_nome = None
        f_cpf = None
        f_ocup = None
        f_email = None
        f_dia = None
        f_mes = None
        f_ano = None
        f_desc = None
    return render_template('profile.html',title='Profile',desc=f_desc,nome=f_nome,cpf=f_cpf,ocup=f_ocup,email=f_email,dia=f_dia,mes=f_mes,ano=f_ano)

@app.route("/profile-edit")
def profileEdit():
    return render_template('profile-edit.html', title='Edit Profile')

@app.route("/edit_info", methods=["POST"])
def editInfo():
    ocup = request.form["ocup"]
    cpf = request.form["cpf"]
    email = request.form["email"]
    desc = request.form["desc"]
    niver = (request.form["niver"]).split("/")

    arvore = None
    arvore = desserializar(arvore)

    found = buscarNo(arvore, "Joao Dowsley")
    found.ocupacao = ocup
    found.cpf = cpf
    found.email = email
    found.desc = desc
    found.niver.dia = int(niver[0])
    found.niver.mes = int(niver[1])
    found.niver.ano = int(niver[2])

    serializar(arvore)

    return redirect(url_for('profile'))


if __name__ == '__main__':
    app.run(debug=True)
