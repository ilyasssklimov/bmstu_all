import "./Footer.css"
import Phone from "../../resources/phone.svg"
import Vk from "../../resources/vk.svg"
import Instagram from "../../resources/instagram.svg"


const Footer = () => {
    return (
        <footer className="footer">
            <a href="https://www.instagram.com" className="instagram">
                <img src={Instagram} alt="Instagram"/>
            </a>
            <a href="https://www.vk.com" className="vk">
                <img src={Vk} alt="Vk"/>
            </a>
            <img src={Phone} alt="Телефон" className="phone"/>
        </footer>
    )
}

export default Footer;