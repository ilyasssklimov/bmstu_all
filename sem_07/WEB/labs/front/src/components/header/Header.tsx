import "./Header.css"
import Logo from "../logo/Logo"
import FiltersButton from "../filtersButton/FiltersButton"
import SearchInput from "../searchInput/SearhInput"
import SearchButton from "../searchButton/SearchButton"
import UsersButton from "../usersButton/UsersButton"
import RegisterButton from "../registerButton/RegisterButton"
import AuthButton from "../authButton/AuthButton"


const Header = () => {
    return (
        <header className="header">
            <Logo/>
            <FiltersButton/>
            <SearchInput/>
            <SearchButton/>
            <UsersButton/>
            <RegisterButton/>
            <AuthButton/>
        </header>
    )
}

export default Header;