import "./UsersButton.css"
import usersButton from "../../resources/usersButton.svg"


const UsersButton = () => {
    return (
        <input type="image" src={usersButton} alt="Люди" className="users_button"/>
    )
}

export default UsersButton;