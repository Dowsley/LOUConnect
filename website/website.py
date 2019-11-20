from flask import Flask, render_template, url_for
app = Flask(__name__)

posts = [
    {
        'nome': 'Lucas Cyrne',
        'desc': 'Blog Post 1',
        'email': 'lcf@cesar.school',
        'cpf': '444.278.278-45',
        'skills': 'Python',
        'id': 'First Post Content',
        'member_since': 'May 28, 1996'
    },
    {
        'nome': 'Eduardo Eile',
        'desc': 'Blog Post 2',
        'email': 'eec@cesar.school',
        'cpf': '999.333.333-66',
        'skills': 'Python, Arduino, Agile', 
        'id': 'Second Post Content',
        'member_since': 'Dez 12, 1998'
    },
]

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
    return render_template('profile.html', title='Profile')

@app.route("/profile-edit")
def profileEdit():
    return render_template('profile-edit.html', title='Edit Profile')


if __name__ == '__main__':
    app.run(debug=True)