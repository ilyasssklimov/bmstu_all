import "./Logo.css"
import logoDisabled from "../../resources/logoDisabled.svg"


const Logo = () => {
    return (
        <input type="image" src={logoDisabled} alt="Логотип" className="logo"/>
    )
}

export default Logo;