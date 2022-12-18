import "./RegisterButton.css"
import registerButton from "../../resources/registerButton.svg"


const RegisterButton = () => {
    return (
        <input type="image" src={registerButton} alt="Регистрация" className="register_button"/>
    )
}

export default RegisterButton;