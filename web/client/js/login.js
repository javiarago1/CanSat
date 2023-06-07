window.addEventListener("load", main)

function main() {
    const sessionToken = localStorage.getItem('sessionToken');
    if (sessionToken) {
        document.getElementById("profile-name").innerText = "Admin";
        document.getElementById("sign-out").style.visibility = "visible";
    }
    document.getElementById('reset-button').addEventListener('click', () => {
        showResetAlert();
    });
    document.getElementById('sign-out').addEventListener('click', logout);



}

// main.js
// Validar el formulario de inicio de sesión

// Función que muestra la alerta de reinicio
function showResetAlert() {
    const sessionToken = localStorage.getItem('sessionToken');
    if (!sessionToken) {
        Swal.fire({
            title: 'Login Form',
            html: `<input type="text" id="login" class="swal2-input" placeholder="Username">
  <input type="password" id="password" class="swal2-input" placeholder="Password">`,
            confirmButtonText: 'Sign in',
            focusConfirm: false,
            preConfirm: () => {
                const login = Swal.getPopup().querySelector('#login').value
                const password = Swal.getPopup().querySelector('#password').value
                if (!login || !password) {
                    Swal.showValidationMessage(`Please enter login and password`)
                }
                return {login: login, password: password}
            }
        }).then((result) => {
            let username = result.value.login
            let password = result.value.password
            fetch('http://164.90.209.79:3000/login', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({username, password})
            })
                .then((response) => {
                    if (response.ok) {
                        return response.json();
                    } else {
                        // Mostrar un error
                    }
                })
                .then((data) => {
                    // Almacenar el token de sesión en el navegador
                    localStorage.setItem('sessionToken', data.token);
                    document.getElementById("profile-name").innerText = "Admin";
                    // Habilitar el botón de reinicio
                    document.getElementById("sign-out").style.visibility = "visible";
                });

        })
    } else {
        Swal.fire({
            title: '¿Estás seguro de reiniciar Redis y MySQL?',
            text: 'Esta acción no se puede deshacer',
            icon: 'warning',
            showCancelButton: true,
            confirmButtonText: 'Sí, reiniciar',
            cancelButtonText: 'No, cancelar'
        }).then((result) => {
            if (result.value) {
                // Enviar solicitud para reiniciar Redis y MySQL
                sendResetRequest();
            }
        });
    }

}

// Función que envía la solicitud de reinicio
function sendResetRequest() {


    // Enviar solicitud HTTP al servidor
    fetch('http://64.226.98.98:3000/reset-services', {
        method: 'POST',
        headers: {
            'Authorization': `Bearer ${localStorage.getItem('sessionToken')}`,
            'Content-Type': 'application/json'
        }
    })
        .then((response) => {
            if (response.ok) {
                Swal.fire({
                    title: 'Servicios reiniciados',
                    text: 'Redis y MySQL se han reiniciado correctamente',
                    icon: 'success'
                });
                window.location.reload()

            } else {
                Swal.fire({
                    title: 'Error',
                    text: 'Hubo un problema al reiniciar los servicios',
                    icon: 'error'
                });
                logout()
            }
        });

}

function logout(){
    localStorage.removeItem('sessionToken');
    window.location.reload();

}

