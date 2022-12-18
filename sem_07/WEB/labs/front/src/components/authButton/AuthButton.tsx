import "./AuthButton.css"
import authButton from "../../resources/authButton.svg"


const AuthButton = () => {
    return (
        <input type="image" src={authButton} alt="Авторизация" className="auth_button"/>
    )
}

export default AuthButton;