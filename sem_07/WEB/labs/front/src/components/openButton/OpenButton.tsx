import "./OpenButton.css"
import openButtonDisabled from "../../resources/openButtonDisabled.svg"


const OpenButton = () => {
    return (
        <input type="image" src={openButtonDisabled} alt="Открыть" className="open_button" disabled/>
    )
}

export default OpenButton;