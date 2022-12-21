import {BrowserRouter as Router, Route, Switch} from 'react-router-dom';
import Header from "../header/Header"
import Footer from "../footer/Footer"
import MainPage from '../../pages/MainPage';


const App = () => {
    return (
        <Router>
            <div className="app">
                <Header/>
                <main>
                    <Switch>
                        <Route exact path="/">
                            <MainPage/>
                        </Route>
                    </Switch>
                </main>
                <Footer/>
            </div>
        </Router>
)}

export default App